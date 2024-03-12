class Function
	def	initialize(blok)
		@wzor=blok 
	end
	
	def value(x)
		@wzor.call(x)
	end
	
	def zero(a,b,e)
		pomi=a;
		tab = Array.new
		while(pomi<=b)
	
			if value(pomi)==0
				tab << pomi
			end
			pomi = pomi +e
		end
		return tab
		
	end
	
	def field(a,b,e)
		pole = 0.0
		pomi = a
		while(pomi+e <=b)
			pole = pole +self.value(pomi)*e
			pomi = pomi+e
		end
		pole = pole + self.value(pomi)*(b-pomi)
		return pole
	end
	
	def derivative(x)
		return (self.value(x+0.001)-self.value(x))*1000
	end
end

blok = lambda do |x|
	2*x 
	end


f = Function.new(blok)

#print f.value(15)
print f.zero(-2,2,1)
print "\n"
print f.value(-2)
print "\n"
puts f.field(0,5,1)
print f.derivative(14)
