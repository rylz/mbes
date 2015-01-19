#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <GLFW/glfw3.h>

#include <list>
#include <stdexcept>
#include <vector>

using namespace std;



enum player_impulse {
  None = 0,
  Up,
  Down,
  Left,
  Right,
  DropBomb,
};

enum block_fall_action {
  Resting = 0,
  Falling,
};

enum cell_type {
  Empty = 0,
  Circuit,
  Rock,
  Exit,
  Player,
  Item,
  Block,
  RoundBlock,
  GreenBomb,
  YellowBomb,
  YellowBombTrigger,
  RedBomb,
  Explosion,
  ItemDude,
  BombDude,
  LeftPortal,
  RightPortal,
  UpPortal,
  DownPortal,
  HorizontalPortal,
  VerticalPortal,
  Portal,
};

enum explosion_type {
  NormalExplosion = 0,
  ItemExplosion,
};

struct cell_state {
  cell_type type;
  int param;
  bool moved;

  cell_state();
  cell_state(cell_type type, int param = 0, bool moved = false);

  bool is_round() const;
  bool should_fall() const;
  bool destroyable() const;
  bool is_bomb() const;
  bool is_volatile() const;
  bool is_edible() const;
  bool is_pushable_horizontal() const;
  bool is_pushable_vertical() const;
  bool is_dude() const;
  explosion_type explosion_type() const;
  bool is_left_portal() const;
  bool is_right_portal() const;
  bool is_up_portal() const;
  bool is_down_portal() const;
};

struct explosion_info {
  int x;
  int y;
  int size;
  int frames; // how many more frames before it occurs
  explosion_type type;

  explosion_info(int x, int y, int size = 1, int frames = 0,
      explosion_type type = NormalExplosion);
};

struct level_state {
  int w;
  int h;
  int player_x;
  int player_y;
  int num_items_remaining;
  int num_red_bombs;
  bool player_will_drop_bomb;
  bool player_did_win;
  float updates_per_second;
  vector<cell_state> cells;
  list<explosion_info> pending_explosions;

  level_state(int w = 60, int h = 24, int player_x = 1, int player_y = 1);

  cell_state& at(int x, int y);
  const cell_state& at(int x, int y) const;
  void move_cell(int x, int y, player_impulse dir);
  bool player_is_alive() const;
  bool validate() const;

  void exec_frame(enum player_impulse impulse);
};

vector<level_state> load_level_index(const char* filename);