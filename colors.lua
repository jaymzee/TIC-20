-- 32-bit color values (r, g, b, a)

BLACK = 0x000000ff
RED = 0xff0000ff
ORANGE = 0xff8000ff
YELLOW = 0xffff00ff
GREEN = 0x00ff00ff
CYAN = 0x00ffffff
BLUE = 0x0000ffff
MAGENTA = 0xff00ffff
WHITE = 0xffffffff
LIGHT_GRAY = 0xaaaaaaff
DARK_GRAY = 0x555555ff
BROWN = 0xaa5500ff

function display_colors ()
	local x = 100
	local y = 50

	display.text(x, y + 20, "black", BLACK);
	display.text(x, y + 60, "red", RED);
	display.text(x, y + 100, "orange", ORANGE);
	display.text(x, y + 140, "yellow", YELLOW);
	display.text(x, y + 180, "green", GREEN);
	display.text(x, y + 220, "cyan", CYAN);
	display.text(x, y + 260, "blue", BLUE);
	display.text(x, y + 300, "magenta", MAGENTA);
	display.text(x, y + 340, "white", WHITE);
	display.text(x, y + 380, "light gray", LIGHT_GRAY);
	display.text(x, y + 420, "dark gray", DARK_GRAY);
	display.text(x, y + 460, "brown", BROWN);
end

if __name__ == 'colors.lua' then
	display.clear(BLACK)
	display_colors()
	delay(5000)
end
