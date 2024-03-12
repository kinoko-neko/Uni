class Integer
	def czynnik
		wyn=Array.new
		pomi=self
		wsk=0
		czyn=2
		if (pomi<2 && pomi>-2)
			wyn[0]=pomi
			return wyn
		end
		
		if pomi<0
			pomi=-pomi
			wyn[0]=-1
			wsk=1
		end
		while czyn*czyn<pomi
			if (pomi%czyn==0)
				wyn[wsk]=czyn
				pomi/=czyn
				wsk+=1
			else
				czyn+=1
			end
		end
		
		if pomi!=1
			wyn[wsk]=pomi
		end
		return wyn
	end
	
	def ack(y)
		if self==0
			return y+1
		elsif y==0
			return (self-1).ack(1)
		else
			return (self-1).ack(self.ack(y-1))
		end
	end
	
	def doskonala
		pomi=2
		suma=1
		while pomi<self
			if self%pomi==0
				suma+=pomi
			end
			pomi+=1
		end
		return suma==self
	end
	
	def slownie
		slow = Array.new
		pomi=self
		if pomi==0
			return "zero"
		end 

		while pomi!=0
			mod=pomi%10
			pomi/=10
			case
				when mod==0
					slow << "zero"
				when mod==1 
					slow << "jeden"
				when mod==2
					slow << "dwa"
				when mod==3
					slow << "trzy"
				when mod==4
					slow << "cztery"
				when mod==5
					slow << "piec"
				when mod==6
					slow << "szesc"
				when mod==7
					slow << "siedem"
				when mod==8
					slow << "osiem"
				when mod==9
					slow << "dziewiec"
			end
		end
		slow.reverse!
		return slow.join(" ")
	end
end

print 6.doskonala
print "\n"
print 1.ack(1)
print "\n"
print 6.czynnik
print "\n"
print 123.slownie
