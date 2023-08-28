function v = cdf(x)
  if (x <= 0)
    v = 0;
  elseif (x <= 1)
    v = x*x/9;
  elseif (x <= 4)
    v = (2*x-1)/9;
  elseif (x <= 6)
    v = (12*x-x*x-18)/18;
  else
    v = 1;
  endif
endfunction
