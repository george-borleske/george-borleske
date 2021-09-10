clear
close all

ls_size     = 20;
start       = 10; 
last        = 100;
first_alpha = 39; 
last_alpha  = 105;
xx2         = start:last;         % frames for stress and strain
xx          = start+ls_size:last; % frames of interest for compliance matrix, young's modulus, and engineering constants
[~, mx2]    = size(xx2);
[~, mx]     = size(xx);
yy          = start+1:last-ls_size+1;
temp        = [];



for i = first_alpha:last_alpha
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Engineering Constants for isotropic material %
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    Name = ['node', num2str(i), '_eng_const_iso.txt'];
    if exist(Name, 'file')
        A=importdata(Name);
        [m,n] = size(A);
        
        young1   = nanmedian(A(yy,2)); % E
        poisson1 = nanmedian(A(yy,3)); % v
        shear1   = nanmedian(A(yy,4)); % G from stress and strain
        shear2   = nanmedian(A(yy,5)); % G from G = E/(2+2v)
        
        eng = ones(4,m);
        eng(1,:) = eng(1,:) * young1;
        eng(2,:) = eng(2,:) * poisson1;
        eng(3,:) = eng(3,:) * shear1;
        eng(4,:) = eng(4,:) * shear2;
        
        i
        temp = [temp; '   ', num2str(i,'%03d'), ' & ', num2str(young1,'%+9.4e'), ' & ', num2str(poisson1,'%+9.4e'), ' & ', num2str(shear1,'%+9.4e'), ' \\ \hline'];
%         figure;
%         subplot(3,1,1);
%         plot(xx,A(yy,2),xx,eng(1,yy))
%         title(['Youngs Mod (E), Node ', num2str(i)])
%         
%         subplot(3,1,2);
%         plot(xx,A(yy,3),xx,eng(2,yy))
%         title('Poisson ratio (v)')
%         
%         subplot(3,1,3);
%         plot(xx,A(yy,5),xx,eng(4,yy))
%         title('Shear Mod (G)')
%         legend('from G = E/(2+2v)', 'E/(2+2v) med')
    end
end

temp

