#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

// A board-copy-free layered beam.
// Problem must provide:
//   using Move, Undo, Score;
//   void enumerate(F emit) const;        // emit(Move)
//   Undo apply(Move);
//   void undo(const Undo&);
//   Score evaluate() const;              // smaller is better
//   uint64_t hash() const;
//   bool complete() const;
// Only one mutable Problem exists. Active nodes are visited in DFS order and
// the state moves between adjacent paths by undoing/applying their suffixes.
namespace inplace_beam {

template<class Problem>
class Search {
 public:
  using Move = typename Problem::Move;
  using Undo = typename Problem::Undo;
  using Score = typename Problem::Score;

  struct Config {
    int width = 1000;
    int depth = 16;
    bool deduplicate = true;
    int reserve_branching = 24;
    // Optional local pruning by immediate score before global hash dedup.
    // Zero keeps every generated candidate.
    int max_candidates_per_parent = 0;
    // Of the local quota, keep this many additional candidates selected by a
    // deterministic hash priority from outside the immediate-score elite.
    int diverse_candidates_per_parent = 0;
    bool prune_root = true;
    // Receding-horizon users may explicitly request the best path from the
    // deepest reached layer when no complete solution exists.
    bool return_frontier_if_incomplete = false;
    bool best_frontier_across_depth = false;
  };

 private:
  struct Node { int parent; Move move; int depth; };
  struct Candidate {
    Score score;
    uint64_t hash;
    int parent_node;
    int parent_order;
    Move move;
  };

  Problem& problem_;
  Config config_;
  std::vector<Node> nodes_;
  std::vector<int> active_;
  std::vector<int> current_path_;
  std::vector<int> target_path_;
  std::vector<Undo> undo_path_;
  std::vector<Candidate> candidates_;
  std::vector<Candidate> local_candidates_;
  // Reused open-addressing table. Stamps make a new layer O(1) to clear and
  // avoid the per-entry node allocations of std::unordered_map.
  std::vector<uint64_t> hash_keys_;
  std::vector<size_t> hash_indices_;
  std::vector<uint32_t> hash_stamps_;
  uint32_t hash_generation_=0;

  size_t hash_slot(uint64_t hash) const {
    size_t slot=(size_t)(hash^(hash>>32))&(hash_keys_.size()-1);
    while (hash_stamps_[slot]==hash_generation_ && hash_keys_[slot]!=hash)
      slot=(slot+1)&(hash_keys_.size()-1);
    return slot;
  }

  void move_to(int node_id) {
    target_path_.clear();
    for (int at=node_id; at>0; at=nodes_[at].parent) target_path_.push_back(at);
    std::reverse(target_path_.begin(), target_path_.end());
    int common=0;
    while (common<(int)target_path_.size() && common<(int)current_path_.size()
           && target_path_[common]==current_path_[common]) ++common;
    while ((int)current_path_.size()>common) {
      problem_.undo(undo_path_.back());
      undo_path_.pop_back(); current_path_.pop_back();
    }
    for (int i=common;i<(int)target_path_.size();++i) {
      undo_path_.push_back(problem_.apply(nodes_[target_path_[i]].move));
      current_path_.push_back(target_path_[i]);
    }
  }

  std::vector<Move> restore_path(int parent, const Move& last) const {
    std::vector<Move> result{last};
    for (int at=parent;at>0;at=nodes_[at].parent) result.push_back(nodes_[at].move);
    std::reverse(result.begin(),result.end());
    return result;
  }

 public:
  Search(Problem& problem, Config config):problem_(problem),config_(config) {
    nodes_.push_back({-1,Move{},0}); active_.push_back(0);
    const size_t candidate_reserve=(size_t)config.width
                                  * std::max(1,config.reserve_branching);
    nodes_.reserve((size_t)config.width*(config.depth+1)+1);
    active_.reserve(config.width);
    candidates_.reserve(candidate_reserve);
    local_candidates_.reserve(std::max(1,config.reserve_branching));
    if (config.deduplicate) {
      size_t table_size=1;
      while (table_size<candidate_reserve*2) table_size<<=1;
      hash_keys_.resize(table_size);
      hash_indices_.resize(table_size);
      hash_stamps_.assign(table_size,0);
    }
    current_path_.reserve(config.depth);
    target_path_.reserve(config.depth);
    undo_path_.reserve(config.depth);
  }

  std::vector<Move> run() {
    // Reuse allocated buffers when the same Search serves repeated replans.
    nodes_.clear(); active_.clear(); current_path_.clear(); target_path_.clear();
    undo_path_.clear(); candidates_.clear(); local_candidates_.clear();
    nodes_.push_back({-1,Move{},0}); active_.push_back(0);
    bool found_complete=false;
    Score best_score=std::numeric_limits<Score>::max();
    int best_parent=-1;
    Move best_last{};
    bool found_frontier=false;
    Score frontier_score=std::numeric_limits<Score>::max();
    int frontier_parent=-1;
    Move frontier_last{};
    for (int depth=0;depth<config_.depth && !active_.empty();++depth) {
      candidates_.clear();
      if (config_.deduplicate) {
        if (++hash_generation_==0) {
          std::fill(hash_stamps_.begin(),hash_stamps_.end(),0);
          hash_generation_=1;
        }
      }
      for (int order=0;order<(int)active_.size();++order) {
        int parent=active_[order]; move_to(parent);
        local_candidates_.clear();
        problem_.enumerate([&](const Move& move) {
          Undo undo=problem_.apply(move);
          Score score=problem_.evaluate();
          uint64_t hash=problem_.hash();
          if (problem_.complete()) {
            // Basic contract: complete is terminal, so do not put it back in
            // the beam. Problems where complete states remain expandable need
            // a problem-specific policy instead.
            if (!found_complete || score<best_score) {
              found_complete=true;
              best_score=score;
              best_parent=parent;
              best_last=move;
            }
            problem_.undo(undo);
            return;
          }
          Candidate candidate{score,hash,parent,order,move};
          local_candidates_.push_back(candidate);
          problem_.undo(undo);
        });
        // Preserve every root move: a temporarily bad setup move can become
        // valuable only after several plies. Most work is below the root.
        if ((depth>0 || config_.prune_root) && config_.max_candidates_per_parent>0 &&
            (int)local_candidates_.size()>config_.max_candidates_per_parent) {
          int diverse=std::min(config_.diverse_candidates_per_parent,
                               config_.max_candidates_per_parent);
          int elite=config_.max_candidates_per_parent-diverse;
          std::nth_element(local_candidates_.begin(),local_candidates_.begin()+elite,
                           local_candidates_.end(),
                           [](const Candidate&a,const Candidate&b){return a.score<b.score;});
          if (diverse>0) {
            auto first=local_candidates_.begin()+elite;
            std::nth_element(first,first+diverse,local_candidates_.end(),
              [](const Candidate&a,const Candidate&b){
                auto mix=[](uint64_t x){x^=x>>30;x*=0xbf58476d1ce4e5b9ULL;
                  x^=x>>27;x*=0x94d049bb133111ebULL;return x^(x>>31);};
                return mix(a.hash)<mix(b.hash);
              });
          }
          local_candidates_.resize(config_.max_candidates_per_parent);
        }
        for (const Candidate& candidate:local_candidates_) {
          if (config_.deduplicate) {
            uint64_t hash=candidate.hash;
            size_t slot=hash_slot(hash);
            if (hash_stamps_[slot]!=hash_generation_) {
              hash_stamps_[slot]=hash_generation_;
              hash_keys_[slot]=hash;
              hash_indices_[slot]=candidates_.size();
              candidates_.push_back(candidate);
            } else if (candidate.score<candidates_[hash_indices_[slot]].score) {
              // Keep the best representative before applying the beam width.
              candidates_[hash_indices_[slot]]=candidate;
            }
          } else {
            candidates_.push_back(candidate);
          }
        }
      }
      if (candidates_.empty()) break;
      int keep=std::min(config_.width,(int)candidates_.size());
      if ((int)candidates_.size()>keep) {
        std::nth_element(candidates_.begin(),candidates_.begin()+keep,candidates_.end(),
          [](const Candidate&a,const Candidate&b){return a.score<b.score;});
        candidates_.resize(keep);
      }
      // Keep frontier information separate from the complete incumbent.
      auto frontier_it=std::min_element(
          candidates_.begin(),candidates_.end(),
          [](const Candidate&a,const Candidate&b){return a.score<b.score;});
      if (!found_frontier || !config_.best_frontier_across_depth
          || frontier_it->score<frontier_score) {
        found_frontier=true;
        frontier_score=frontier_it->score;
        frontier_parent=frontier_it->parent_node;
        frontier_last=frontier_it->move;
      }
      // Restores DFS order for cheap transitions in the next layer.
      std::sort(candidates_.begin(),candidates_.end(),[](const Candidate&a,const Candidate&b){
        if(a.parent_order!=b.parent_order)return a.parent_order<b.parent_order;
        return a.hash<b.hash;
      });
      active_.clear(); active_.reserve(candidates_.size());
      for (auto& c:candidates_) {
        nodes_.push_back({c.parent_node,c.move,depth+1});
        active_.push_back((int)nodes_.size()-1);
      }
    }
    move_to(0);
    // Path allocation/reconstruction happens exactly once, after the search.
    if (found_complete) return restore_path(best_parent,best_last);
    if (config_.return_frontier_if_incomplete && found_frontier)
      return restore_path(frontier_parent,frontier_last);
    return {};
  }
};
} // namespace inplace_beam

// NOTE: Problem::evaluate() should preferably be O(1). Update its score in
// apply() and restore it in undo() instead of rescanning the whole state.
// NOTE: Problem::hash() should preferably be O(1), using incremental Zobrist,
// XOR, or another reversible hash update in apply()/undo().
// NOTE: Candidate size affects cache efficiency when branching is large.
// Compact Move where the problem permits it; roughly 16-32 bytes per candidate
// is a useful target, but this generic template does not force packing.
// NOTE: parent_order sorting is appropriate for beams of thousands. At widths
// of tens or hundreds of thousands, parent_order's bounded integer range can
// support bucket/counting-sort-style ordering.
// Dedup uses reusable open addressing with generation stamps, avoiding per-layer
// clearing and node allocation. The table is sized from reserve_branching, so
// configure that estimate high enough to keep the load factor below one half.
// NOTE: Config::reserve_branching is problem dependent; set it near the average
// number of emitted moves per active state to reduce reallocations without
// excessive memory reservation.
// NOTE: This implementation treats complete as terminal. If complete means
// merely "currently valid but still improvable", customize the complete branch
// and define how such states compete with unfinished candidates.
// NOTE: 64-bit hash deduplication can collide. Strict applications may use a
// 128-bit hash, an extra fingerprint, or an equality check on collisions.
