require 'colors'

POINTS = 500
CX = 640
CY = 512
R = 400

KEEP_RUNNING = 0x55aa -- flag in TIC memory (readonly)

function frame (factor)
	display.clear(BLACK)
	for n = 0, POINTS do
		local n1 = n
		local n2 = factor * n1
		local theta = 2 * math.pi * n1 / POINTS
		local phi = 2 * math.pi * n2 / POINTS
		local x1 = R * math.cos(theta)
		local y1 = R * math.sin(theta)
		local x2 = R * math.cos(phi)
		local y2 = R * math.sin(phi)
		display.line(CX - x1, CY - y1, CX - x2, CY - y2)
	end
	--display.text(10, 10, string.format("factor %.1f", factor), YELLOW)
	delay(100)
end

function main ()
	local factor

	print('see the video:')
	print('Times Tables, Mandelbrot and the Heart of Mathematics')
	print('by Mathologer')

	display.pencolor(0x00ff0040)

	factor = 1
	while peek(KEEP_RUNNING) ~= 0 do
		frame(factor)
		factor = factor + 0.05
	end
end

main()
