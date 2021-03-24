#define OLC_PGE_APPLICATION
#include "Game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
int main()
{
#ifdef __EMSCRIPTEN__
	EM_ASM(
		FS.mkdir('/store');
		FS.mount(IDBFS, {}, '/store');
		FS.syncfs(true, function(err) { if (err) alert("Error on syncing FS: " + err);	});
	);
#endif

	Game game;
	if (game.Construct(400, 400, 2, 2))
		game.Start();
	return 0;
}