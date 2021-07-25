green = 0x00ff0040
yellow = 0xffff00ff
black = 0x000000ff
fps = 30

points = 500
cx = 320
cy = 240
radius = 200
factor = 2

print("Hello from lua")

pencolor(green)

function draw_frame(factor)
	local n1, n2, theta, phi, x1, y1, x2, y2

	clear(black)

	for n = 0, points do
		n1 = n
		n2 = factor * n1
		theta = 2 * math.pi * n1 / points
		phi = 2 * math.pi * n2 / points
		x1 = radius * math.cos(theta)
		y1 = radius * math.sin(theta)
		x2 = radius * math.cos(phi)
		y2 = radius * math.sin(phi)
		line(cx - x1, cy - y1, cx - x2, cy - y2)
	end

	flip()
end

function main()
	local factor

	factor = 1
	for n = 1, 1000 do
		draw_frame(factor)
		factor = factor + 0.001
	end
end

main()
