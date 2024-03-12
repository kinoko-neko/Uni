class Function
	def	initialize(blok)
		@wzor=blok 
	end
	
	def value(x,y)
		@wzor.call(x,y)
	end
	
	def volume(a,b,c,d,e)
		p1=a
		pole=0.0
		podstawa = e*e
		while p1+e<=b
			p2=c
			while p2+e<=d 
			pole = pole +	podstawa*value(p1,p2)
			p2 = p2 + e
			end
			p1 = p1+e
		end
		return pole
	end
	
	def contour_line(a,b,c,d,step,acuracy,height)
		p1=a
		tab = Array.new
		
		while p1<=b
			p2=c
			while p2<=d 
			pom2 = value(p1,p2)
 			if pom2<=height+acuracy && pom2>=height-acuracy
 				tab << [p1,p2]
			end
			p2 = p2 + step
			end
			p1 = p1+step
		end
		return tab
	end
end

blok = lambda do |x,y|
	2*x +y
	end

f = Function.new(blok)

puts f.value(1,2)

stala = lambda do |x,y|
	5
	end

f2 = Function.new(stala)

puts f2.volume(1,3,1,3,1)

print f.contour_line(1,3,1,3,1,0.1,5)

