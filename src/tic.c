#include <assert.h>
#include <lualib.h>
#include <lauxlib.h>
#include "display.h"
#include "tic.h"

// add C function to a lua table
#define addfunction(L, f) lua_pushcfunction(L, f); \
                          lua_setfield(L, -2, #f);

static const char *error_message = NULL;

// 64 KB of ram
volatile uint8_t ram[0x10000];

// Retreive the Display base address from lua globals.
// It's stored as a lua number (double precision) which works on current
// amd64 hardware but will fail on hareware that uses more than 52 bits for
// virtual addresses. Right now it's only 48 bits and that fits within
// a double precision mantissa (52 bits).
//
// This trick is also used by some implementation of javascript and allows
// all native types to be stored within a double precision floating point
// number. An extra 4 bits are available for something like a tag. Even more
// bits can be stolen if you consider alignment.
static Display *GetDisplay(lua_State *L)
{
    lua_getglobal(L, "__display__");
    Display *display = (Display *)(intptr_t)luaL_checknumber(L, -1);
    lua_pop(L, 1);

    return display;
}

static int clear(lua_State *L)
{
    Display *display = GetDisplay(L);
    unsigned int color = luaL_checknumber(L, 1);

    ClearScreen(display, color);

    return 0;
}

static int pencolor(lua_State *L)
{
    Display *display = GetDisplay(L);
    unsigned int color = luaL_checknumber(L, 1);

    PenColor(display, color);

    return 0;
}

static int text(lua_State *L)
{
    Display *display = GetDisplay(L);
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    const char *s = luaL_checkstring(L, 3);
    unsigned int color = luaL_checknumber(L, 4);

    if (!DrawText(display, x, y, s, color)) {
        luaL_error(L, "DrawText failed");
    }

    return 0;
}

static int line(lua_State *L)
{
    Display *display = GetDisplay(L);
    double x1 = luaL_checknumber(L, 1);
    double y1 = luaL_checknumber(L, 2);
    double x2 = luaL_checknumber(L, 3);
    double y2 = luaL_checknumber(L, 4);

    DrawLine(display, x1, y1, x2, y2);

    return 0;
}

static int point(lua_State *L)
{
    Display *display = GetDisplay(L);
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);

    DrawPoint(display, x, y);

    return 0;
}

static int delay(lua_State *L)
{
    unsigned int msec = luaL_checknumber(L, 1);

    Delay(msec);

    return 0;
}

static int peek(lua_State *L)
{
    int addr = luaL_checknumber(L, 1);

    if (addr < 0 || addr > 0xffff) {
        luaL_error(L, "address must be within 0 to 0xffff");
    }

    lua_pushinteger(L, ram[addr]);

    return 1;
}

static int poke(lua_State *L)
{
    //unsigned int addr = luaL_checknumber(L, 1);
    //unsigned int data = luaL_checknumber(L, 2);

    return 0;
}

int TicExec(const char *filename, Display *display)
{
    // Create new Lua state and load the lua libraries
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Expose C functions to the lua environment
    lua_newtable(L);
    addfunction(L, clear);
    addfunction(L, pencolor);
    addfunction(L, text);
    addfunction(L, line);
    addfunction(L, point);
    lua_setglobal(L, "display");

    lua_pushcfunction(L, delay);
    lua_setglobal(L, "delay");
    lua_pushcfunction(L, peek);
    lua_setglobal(L, "peek");
    lua_pushcfunction(L, poke);
    lua_setglobal(L, "poke");

    lua_pushstring(L, filename);
    lua_setglobal(L, "__name__");
    lua_pushnumber(L, (intptr_t)display);
    lua_setglobal(L, "__display__");

    // Tell Lua to execute a lua file
    int status = luaL_dofile(L, filename);
    if (status) {
        error_message = luaL_checkstring(L, -1);
    }

    return status;
}

// retreive saved error message
const char *TicError(void) {
    return error_message;
}
