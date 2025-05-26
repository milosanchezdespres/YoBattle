#include "retrocs/retrocs.h"

int main()
{
    VirtualScreen screen_space = VirtualScreen();

    int id = screen_space.spawn_at(2, 2);
    int id2 = screen_space.spawn_at(8, 3);
    int id3 = screen_space.spawn_at(28, 22);

    screen_space.remove(id2);
    id2 = screen_space.spawn_at(8, 3);

    debug(id);
    debug(screen_space.tile(id));
    debug(screen_space.entity_id_at(2, 2));
    debug(".................................................");

    debug(id2);
    debug(screen_space.tile(id2));
    debug(screen_space.entity_id_at(8, 3));
    debug(".................................................");

    debug(id3);
    debug(screen_space.tile(id3));
    debug(screen_space.entity_id_at(28, 22));
    debug(".................................................");

    screen_space.update(id3, 42, 50);

    debug(id3);
    debug(screen_space.tile(id3));
    debug(screen_space.entity_id_at(42, 50));
    debug(".................................................");
    debug(screen_space.entity_id_at(28, 22));

    return 0;
}