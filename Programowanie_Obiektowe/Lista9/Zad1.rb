class Function
    @funkcja
    def initialize(funkcja)
        @funkcja = funkcja
    end

    def value(x)
        return @funkcja.call(x)
    end

    def zero(a, b, e)
        m_zerowe = []
        i=a
        while i <= b
            if self.value(i) * self.value(i+e) <=0
                m_zerowe.append(i)
            end
            i += e
        end    
        if m_zerowe.length() == 0
            return nil
        end
        return m_zerowe
    end

    def field(a, b)
        e = 0.00001
        dx = (b.to_f-a.to_f)*e
        suma = 0
        i=a
        while i<b
            suma += self.value(i)*dx
            i += dx
        end 
        return suma
    end

    def deriv(x)
        h = 0.00001
        return (self.value(x+h)-self.value(x))/h
    end
end


f = Function.new(proc { |x| x*x-2})
puts "Funkcja f(x)=x^2-2"
puts "Wartość funkcji dla x=-7"
puts f.value(-7)
puts "Miejsca zerowe funkcji na przedziale [-10, 10] z dokładnościa e=0.0001"
puts f.zero(-10, 10, 0.0001).join(', ')

g = Function.new(proc { |x| x*x})
puts "\nFunkcja g(x)=x^2"
puts "Przybliżone pole powierzchni pod wykresem na przedziale [0, 2]"
puts g.field(0, 2)
puts "Przybliżona pochodna funkcji w punkcie x=3"
puts g.deriv(3)