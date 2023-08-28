function v = z4(n, k, x)
  len = length(x);
  v = zeros(1, len);
  const_factor = n * nchoosek(n-1, k-1);
  for i = 1 : len
    xi = x(i);
    cdf_val = cdf(xi);
    v(i) = const_factor * pdf(xi) * cdf_val^(k-1) * (1-cdf_val)^(n-k);
  endfor
endfunction
