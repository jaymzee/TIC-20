#include <lualib.h>
#include <lauxlib.h>
#include "lua.h"
#include "screen.h"

extern struct Screen *screen;
static const char *error = NULL;

static int clear(lua_State *L)
{
    unsigned int color = luaL_checknumber(L, 1);

    ClearScreen(screen, color);

    return 0;    // number of results
}

static int pencolor(lua_State *L)
{
    unsigned int color = luaL_checknumber(L, 1);

    SetPenColor(screen, color);

    return 0;   // number of results
}

static int text(lua_State *L)
{
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    const char *s = luaL_checkstring(L, 3);
    unsigned int color = luaL_checknumber(L, 4);

    DrawText(screen, x, y, s, 0, color);

    return 0;   // number of results
}

static int line(lua_State *L)
{
    //check and fetch the arguments
    double x1 = luaL_checknumber(L, 1);
    double y1 = luaL_checknumber(L, 2);
    double x2 = luaL_checknumber(L, 3);
    double y2 = luaL_checknumber(L, 4);

    DrawLine(screen, x1, y1, x2, y2);

    return 0;   // number of results
}

static int flip(lua_State *L)
{
    Flip(screen);

    return 0;   // number of results
}

static int delay(lua_State *L)
{
    unsigned int msec = luaL_checknumber(L, 1);

    Delay(msec);

    return 0;   // number of results
}

int LuaMain(const char *filename)
{
    // Create new Lua state and load the lua libraries
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Expose the C functions to the lua environment
    lua_pushcfunction(L, clear);
    lua_setglobal(L, "clear");
    lua_pushcfunction(L, pencolor);
    lua_setglobal(L, "pencolor");
    lua_pushcfunction(L, text);
    lua_setglobal(L, "text");
    lua_pushcfunction(L, line);
    lua_setglobal(L, "line");
    lua_pushcfunction(L, flip);
    lua_setglobal(L, "flip");
    lua_pushcfunction(L, delay);
    lua_setglobal(L, "delay");

    // Tell Lua to execute a lua file
    int exitcode = luaL_dofile(L, filename);
    if (exitcode != LUA_OK) {
        // save error message
        error = luaL_checkstring(L, -1);
    }

    return exitcode;
}

// retreive saved error message
const char *GetLuaError(void) {
    return error;
}
