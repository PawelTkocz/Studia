disp("Funkcja obliczajaca wartosc dystrubuanty w punkcje x")
output_precision(10)

function d = density(mi, sigma, x)
#gestosc rozkladu normalnego X~N(mi, sigma^2)
d = 1/(sqrt(2*pi)*sigma)*exp(-(x-mi)^2/(2*sigma^2));
endfunction

function res = integ(mi, sigma, a, b, max_b)
#wartosc calki na ograniczonym przedziale
#obliczana z wykorzystaniem zlozonego wzoru trapezow
if (b > max_b)
  b = max_b;
endif
if (a >= b)
  res = 0;
  return
endif
n = 10000;
h = (b-a)/n;
res = (density(mi, sigma, a) + density(mi, sigma, b))/2;
for i = 1 : n-1
  res = res + density(mi, sigma, a+i*h);
end
res = h*res;
endfunction

function v = dystrybuanta (mi, sigma, x)
#wartosc dystrybuanty obliczona poprzez
#policzenie calki na kilku rozlacznych przedzialach
v1 = integ(mi, sigma, mi-sigma, mi+sigma, x);
v2 = integ(mi, sigma, mi-3*sigma, mi-sigma, x);
v3 = integ(mi, sigma, mi+sigma, mi+3*sigma, x);
v4 = integ(mi, sigma, mi-5*sigma, mi-3*sigma, x);
v5 = integ(mi, sigma, mi+3*sigma, mi+5*sigma, x);
v6 = integ(mi, sigma, mi-50*sigma, mi-5*sigma, x);
v7 = integ(mi, sigma, mi+5*sigma, mi+50*sigma, x);
v8 = integ(mi, sigma, mi+50*sigma, x, x);
v9 = integ(mi, sigma, x-50*sigma, x, mi-50*sigma);
v = v1+v2+v3+v4+v5+v6+v7+v8+v9;
endfunction


dystrybuanta(12, 5, 5.5)
