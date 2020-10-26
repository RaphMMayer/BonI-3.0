
function BTcall(reg,adata,fdata,tdata,object)
%reg 1=channel 1, 2=channel 2, 3=channel 3, 
%0 for turning on/off each channel, 1 is on, 0 is off, adata=channel 1,
%fdata=channel 2, tdata=channel 3
div = ',';
val = strcat(num2str(reg),div,num2str(adata),div,num2str(fdata),div,num2str(tdata));
write(object,val,'string');
end

