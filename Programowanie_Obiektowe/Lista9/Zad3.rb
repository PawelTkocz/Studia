class Function
    @width
    @height
    @funkcja
    def initialize(funkcja)
        @funkcja = funkcja
        @width = 100
        @height = 50
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

    def minmax(a, b)
        dx = (b-a).to_f/@width
        i=a
        min = self.value(i)
        max = min
        while i<=b
            val = self.value(i)
            if val<min
                min = val
            end
            if val>max
                max = val
            end
            i += dx
        end
        return [min-1, max+1]
    end

    def draw(a, b)
        wykres = Array.new(@height){Array.new(@width, 0)}
        minAndMax = minmax(a, b)
        min = minAndMax[0]
        max = minAndMax[1]
        y_span = (max-min+1).to_f
        x_span = (b-a+1).to_f
        dx = x_span/@width

        if min*max <= 0
            ox = (-min/y_span*@height).round
            ox = @height - 1 - ox
            for i in 0..@width-1
                wykres[ox][i]=2
            end
        end

        if a<=0 and b>= 0
            oy = -a/dx
            for i in 0..@height-1
                wykres[i][oy]=3
            end
        end

        for i in 0..@width-1
            y = ((self.value(a+i*dx)-min)/y_span*@height).round
            if y<@height
                y = @height - 1 - y
                wykres[y][i] = 1; 
            end
        end

        for i in 0..@height-1
            for j in 0..@width-1
                if wykres[i][j]==1
                    print "X"
                elsif wykres[i][j]==2
                    print "-"
                elsif wykres[i][j]==3
                    print "|"
                else
                    print " "
                end
            end
            puts
        end
    end    
end

f = Function.new(proc { |x| x*Math.sin(x)-1})
puts "Wykres funkcji f(x)=x*sin(x)-1 na przedziale [-7, 7]"
f.draw(-7, 7)