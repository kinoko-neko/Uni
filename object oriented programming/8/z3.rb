class Jawna
	def initialize(arg)
		@napis=arg
	end
	
	def zaszyfruj(key)
		pomi=@napis.split("")
		siz=pomi.length
		licznik=0
		while licznik<siz
			pomi[licznik]=key[pomi[licznik]]
			licznik+=1
		end
		return Zaszyfrowana.new(pomi.join(""))
	end
	
	def to_s
		return @napis
	end 
end

class Zaszyfrowana
	def initialize(arg)
		@napis=arg
	end
	 
	def odszyfruj(key)
		pomi=@napis.split("")
		siz=pomi.length
		licznik=0
		while licznik<siz
			pomi[licznik]=key[pomi[licznik]]
			licznik+=1
		end
		return Jawna.new(pomi.join(""))
	end
	
	def to_s
		return @napis
	end
end

key = 
{
    "a" => "b",
    "b" => "r",
    "r" => "y",
    "y" => "u",
    "u" => "a"
}

s1 = Zaszyfrowana.new("ruby")
j1 = Jawna.new("ruby")

print s1.to_s
print "\n"
print j1.to_s
print "\n"
s2= j1.zaszyfruj(key)
j2= s1.odszyfruj(key)
print s2.to_s
print "\n"
print j2.to_s
