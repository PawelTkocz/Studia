function v = pdf(x)
  c = 2/9;
  if (x <= 0)
    v = 0;
  elseif (x <= 1)
    v = c*x;
  elseif (x <= 4)
    v = c;
  elseif (x <= 6)
    v = -c/2*x + 3*c;
  else
    v = 0;
  endif
endfunction
