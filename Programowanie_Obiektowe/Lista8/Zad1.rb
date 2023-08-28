class Integer
    def czynniki
        tab = []
        for i in 1..self
            if self%i == 0
                tab.append(i)
            end
        end
        return tab
    end

    def ack(y)
        if self == 0
            return y+1
        elsif y == 0
            (self-1).ack(1)
        else
            (self-1).ack(self.ack(y-1))
        end
    end

    def doskonala
        dzielniki = self.czynniki
        suma=0
        for i in 0..dzielniki.length-2
            suma+=dzielniki[i]
        end
        return suma==self
    end

    def slownie
        res = ""
        pom = self
        while pom > 0
            x = pom % 10;
            case x
            when 0
                res = "zero " + res
            when 1
                res = "jeden " + res
            when 2
                res = "dwa " + res
            when 3
                res = "trzy " + res
            when 4
                res = "cztery " + res
            when 5
                res = "pięć " + res
            when 6
                res = "sześć " + res
            when 7
                res = "siedem " + res
            when 8
                res = "osiem " + res
            when 9
                res = "dziewięć " + res
            end
            pom /= 10;
        end
        return res
    end
end

print 'Dzielniki 24: '
puts 24.czynniki.join(', ')
print 'Ack(2, 1): '
puts 2.ack(1)
print 'Liczba 6 jest doskonała: '
puts 6.doskonala
print 'Liczba 24 jest doskonała: '
puts 24.doskonala
print '123 słownie: '
puts 123.slownie