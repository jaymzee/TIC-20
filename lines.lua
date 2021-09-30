require 'colors'

xmin, ymin = 20, 20
xmax, ymax = 1260, 1004
KEEP_RUNNING = 0x55aa

print('executing ' .. __name__)
delay(500)

display.clear(BLACK)

colors = {[0] = RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, MAGENTA, WHITE}
colornum = 0
x0, y0 = 15, 133
x1, y1 = 531, 25
dx0, dy0 = 1, 1
dx1, dy1 = 1, 1

while peek(KEEP_RUNNING) ~= 0 do
	display.pencolor(colors[colornum])
	display.line(x0, y0, x1, y1)

	x0 = x0 + 10*dx0
	y0 = y0 + 9*dy0
	x1 = x1 + 8*dx1
	y1 = y1 + 7*dy1

	if x0 >= xmax then
		dx0 = -1
		colornum = (colornum + 1) % 8
	end
	if x1 >= xmax then
		dx1 = -1
		colornum = (colornum + 1) % 8
	end
	if y0 >= ymax then
		dy0 = -1
		colornum = (colornum + 1) % 8
	end
	if y1 >= ymax then
		dy1 = -1
		colornum = (colornum + 1) % 8
	end
	if x0 <= xmin then
		dx0 = 1
		colornum = (colornum + 1) % 8
	end
	if x1 <= xmin then
		dx1 = 1
		colornum = (colornum + 1) % 8
	end
	if y0 <= ymin then
		dy0 = 1
		colornum = (colornum + 1) % 8
	end
	if y1 <= ymin then
		dy1 = 1
		colornum = (colornum + 1) % 8
	end
	delay(10)
end
