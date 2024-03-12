class Collection
	def initialize
		@array = Array.new
		@length	=	0
	end
	
	def initialize (tab)
		unless  tab.kind_of?(Array)
			throw "zle dane" 
		end
		@array = tab
		@length	=	tab.length
	end
	
	def spr_index(i)
		unless	i.kind_of?(Integer)
			return false
		end
		if (i> @length or i<0)
			return false
		end
		return true
	end
	
	def get(i)
		throw "zly indeks" if !(self.spr_index(i) )
		return @array[i]
		
	end
	
	def swap(i,j)
		throw "zly indeks" if ( !(self.spr_index(i)) or !(self.spr_index(j)) )
		@array[i], @array[j]	=	@array[j], @array[i] 
	end
	
	def length
		return @length
	end
	
	def print
		p @array
	end
end

class Komparator
	def compare(a,b)
		return a<b
	end
end


class Sorter
	
	def check_cmp(cmp)
		unless cmp.respond_to?("compare")
			return false
		end
		return true
	end

	def sort1(lista, cmp) #bubble sort
		throw "zly komparator" if !self.check_cmp(cmp)
		n = lista.length
		for i in 0..(n-2)
			for j in (i+1)..(n-1)
				lista.swap(i,j) if cmp.compare(lista.get(j),lista.get(i))
			end
		end
	end

	def sort2(lista, cmp) #select sort szybszy niż bubble sort (ma mniejszą stałą asymptotycznie to też n^2)
		throw "zly komparator" if !self.check_cmp(cmp)
		n	=	lista.length
		for i in 0..(n-2)
			mini= lista.get(i)
			mini_poz	=	i
			for	j in (i+1)..(n-1) 
				if	cmp.compare(lista.get(j),mini)
					mini_poz	=	j
					mini	=	lista.get(j)
				end
			end
			lista.swap(i,mini_poz)
		end
	end

end

sort	=	Sorter.new
komp	=	Komparator.new
kol1	=	Collection.new( [ 1,6,3,4,15,265,35,6,-1,-5])
kol2	=	Collection.new([ 1,6,3,4,15,265,35,6,-1,-5])

sort.sort1(kol1,komp)
sort.sort2(kol2,komp)
puts kol1.length
kol1.print
kol2.print

