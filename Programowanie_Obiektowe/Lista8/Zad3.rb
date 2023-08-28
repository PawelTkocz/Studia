class Jawna
    @napis
    def initialize(napis)
        @napis = napis
    end

    def zaszyfruj(key)
        szyfr = ""
        for i in 0..@napis.length-1
            szyfr += key[@napis[i]]
        end
        zaszyfrowane = Zaszyfrowane.new(szyfr)
        return zaszyfrowane
    end

    def to_s
        return @napis
    end
end

class Zaszyfrowane
    @napis
    def initialize(napis)
        @napis = napis
    end

    def odszyfruj(key)
        wiadomosc = ""
        for i in 0..@napis.length-1
            wiadomosc += key.key(@napis[i])
        end
        jawne = Jawna.new(wiadomosc)
        return jawne
    end

    def to_s
        return @napis
    end
end

/przykładowy klucz/
key = { 'z' => 'a'}
for i in 'a'..'y'
    key[i] = (i.ord + 1).chr
end

jawna = Jawna.new("tajnawiadomosc")
print 'Wiadomosc do zaszyfrowania: '
puts jawna.to_s
tajne = jawna.zaszyfruj(key)
print 'Zaszyfrowana wiadomość: '
puts tajne.to_s
jawna2 = tajne.odszyfruj(key)
printf 'Odszyfrowana wiadomość: '
puts jawna2.to_s