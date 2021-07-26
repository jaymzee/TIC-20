require 'colors'

FPS = 30
POINTS = 500
CX = 320
CY = 240
R = 200

function frame (factor)
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
	display.flip()
	display.clear(BLACK)
end

function main ()
	local factor

	print('see the video:')
	print('Times Tables, Mandelbrot and the Heart of Mathematics')
	print('by Mathologer')

	display.pencolor(0x00ff0040)

	factor = 1
	for n = 1,1000,1 do
		frame(factor)
		factor = factor + 0.001
	end
end

main()
