function [output] = XDoG(input,sigma,k,p)

output = imgaussfilt(input,sigma) + p*(imgaussfilt(input,sigma) - imgaussfilt(input,sigma*k));

end