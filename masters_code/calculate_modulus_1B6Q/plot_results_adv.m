clear
close all


%for i=1:nodes
i = 32;
ls_size = 20;
start   = 1;
last    = 399;
xx2     = start:last;         % frames for stress and strain
xx      = start+ls_size:last; % frames of interest for compliance matrix,
                              % young's modulus, and engineering constants
                              
first_alpha = 3;
last_alpha  = 43;
[~, mx2] = size(xx2);
[~, mx] = size(xx);
yy      = start+1:last-ls_size+1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Position of first node of alpha helix %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(first_alpha), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = [1:m];
%     figure;
%     plot(xx,A(xx,2),'b',xx,A(xx,3),'k',xx,A(xx,4),'r')
%     legend('x coordinate', 'y coordinate', 'z coordinate')
%     title('position of node 66 (fixed)')
end
B = A;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Position of last node of alpha helix %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(last_alpha), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = [1:m];
%     figure;
%     plot(xx,A(xx,2),'b',xx,A(xx,3),'k',xx,A(xx,4),'r')
%     legend('x coordinate', 'y coordinate', 'z coordinate')
%     title('position of node 117')
end
% plot bond lengths of each bond
% figure;
% plot(xx,A(xx,2)-B(xx,2),'b',xx,A(xx,3)-B(xx,3),'k',xx,A(xx,4)-B(xx,4),'r')
% legend('x coordinate', 'y coordinate', 'z coordinate')
% title('Components of the Length of alpha helix (distrance between 117 and 66)')
for j=1:m
   D(j) = norm(A(j,2:4)-B(j,2:4)); 
end
figure;
plot(D(:))
title('Length of alpha helix')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Engineering Constants for transversely isotropic material %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_eng_const.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = ls_size:1:m+ls_size-1;
    
    young1   = median(A(yy,2)); % E
    young2   = median(A(yy,3)); % E'
    poisson1 = median(A(yy,4)); % v
    poisson2 = median(A(yy,5)); % v'
    shear1   = median(A(yy,6)); % G
    shear2   = median(A(yy,7)); % G'
    
    eng = ones(6,m);
    eng(1,:) = eng(1,:) * young1;
    eng(2,:) = eng(2,:) * young2;
    eng(3,:) = eng(3,:) * poisson1;
    eng(4,:) = eng(4,:) * poisson2;
    eng(5,:) = eng(5,:) * shear1;
    eng(6,:) = eng(6,:) * shear2;
    
    zz = ones(6,m);
    zz(1,:) = zz(1,:) * 1 / young1;           % S_11 = 1/E
    zz(2,:) = zz(2,:) * (-poisson1 / young1); % S_12 = -v/E
    zz(3,:) = zz(3,:) * (-poisson2 / young2); % S_13 = -v'/E'
    zz(4,:) = zz(4,:) * 1 / young2;           % S_33 = 1/E'
    zz(5,:) = zz(5,:) * 1 / shear2;           % S_44 = 1/G'
    zz(6,:) = zz(6,:) * 1 / shear1;           % S_66 = 1/G
    
    figure;
    subplot(2,3,1);
    plot(xx,A(yy,2),xx,eng(1,yy))
    title('Youngs Mod (E)')
    
    subplot(2,3,2);
    plot(xx,A(yy,3),xx,eng(2,yy))
    title('Youngs Mod (E_0)')
    
    subplot(2,3,3);
    plot(xx,A(yy,4),xx,eng(3,yy))
    title('Poisson ratio (v)')
    
    subplot(2,3,4);
    plot(xx,A(yy,5),xx,eng(4,yy))
    title('Poisson ratio (v_0)')
    
    subplot(2,3,5);
    plot(xx,A(yy,6),xx,eng(5,yy))
    title('Shear Mod (G)')
    
    subplot(2,3,6);
    plot(xx,A(yy,7),xx,eng(6,yy))
    title('Shear Mod (G_0)')
    
    %saveas(gcf, ['node', num2str(i), '_strain'])
    %saveas(h,['node', num2str(i), '_strain','.eps'],'eps')
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stress %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_stress.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    
    % linear regression for xx component of stress
    lin_reg_str = zeros(6,mx2);
    for j = 1:6
       coef_str =  [ones(mx2,1) xx2'] \ A(xx2,j+1);
       lin_reg_str(j,:) = coef_str(1) + coef_str(2) * xx2;
    end

   
    figure;
    subplot(2,3,1);
    plot(xx2,A(xx2,2),xx2,lin_reg_str(1,:))
    title('XX Stress')
    legend('every frame', 'linear regression')
    
    subplot(2,3,2);
    plot(xx2,A(xx2,3),xx2,lin_reg_str(2,:))
    title('YY')
    
    subplot(2,3,3);
    plot(xx2,A(xx2,4),xx2,lin_reg_str(3,:))
    title('ZZ')
    
    subplot(2,3,4);
    plot(xx2,A(xx2,5),xx2,lin_reg_str(4,:))
    title('ZX')
    
    subplot(2,3,5);
    plot(xx2,A(xx2,6),xx2,lin_reg_str(5,:))
    title('ZY')
    
    subplot(2,3,6);
    plot(xx2,A(xx2,7),xx2,lin_reg_str(6,:))
    title('XY')
    
    %saveas(gcf, ['node', num2str(i), '_stress'])
    %saveas(h,['node', num2str(i), '_stress','.eps'],'eps')
end
B = A;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Strain %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_strain.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A); 
    
    % linear regression for xx component of stress
    lin_reg_def = zeros(6,mx2);
    for j = 1:6
       coef_str =  [ones(mx2,1) xx2'] \ A(xx2,j+1);
       lin_reg_def(j,:) = coef_str(1) + coef_str(2) * xx2;
    end
    
    figure;
    subplot(2,3,1);
    plot(xx2,A(xx2,2),xx2,lin_reg_def(1,:))
    title('XX Strain')
    legend('every frame', 'linear regression')
    
    subplot(2,3,2);
    plot(xx2,A(xx2,3),xx2,lin_reg_def(2,:))
    title('YY')
    
    subplot(2,3,3);
    plot(xx2,A(xx2,4),xx2,lin_reg_def(3,:))
    title('ZZ')
    
    subplot(2,3,4);
    plot(xx2,A(xx2,5),xx2,lin_reg_def(4,:))
    title('ZX')
    
    subplot(2,3,5);
    plot(xx2,A(xx2,6),xx2,lin_reg_def(5,:))
    title('ZY')
    
    subplot(2,3,6);
    plot(xx2,A(xx2,7),xx2,lin_reg_def(6,:))
    title('XY')
    
    %saveas(gcf, ['node', num2str(i), '_strain'])
    %saveas(h,['node', num2str(i), '_strain','.eps'],'eps')
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stress/Strain %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Strain is A (y-axis)
% Stress is B (x-axis)
figure;
subplot(2,3,1);
scatter(B(xx2,2),A(xx2,2))
title('XX')
xlabel('Stress')
ylabel('Strain')

subplot(2,3,2);
scatter(B(xx2,3),A(xx2,3))
title('YY')

subplot(2,3,3);
scatter(B(xx2,4),A(xx2,4))
title('ZZ')

subplot(2,3,4);
scatter(B(xx2,5),A(xx2,5))
title('ZX')

subplot(2,3,5);
scatter(B(xx2,6),A(xx2,6))
title('ZY')

subplot(2,3,6);
scatter(B(xx2,7),A(xx2,7))
title('XY')

%saveas(gcf, ['node', num2str(i), '_strain'])
%saveas(h,['node', num2str(i), '_strain','.eps'],'eps')


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Compliance Matrix %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node_comp_', num2str(i), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A); 
    
    figure;
    subplot(2,3,1);
    plot(xx,A(yy,2),xx,zz(1,yy),'r')
    title('XX (S_11) Compliance Matrix')
    legend('every step', 'median')
    
    subplot(2,3,2);
    plot(xx,A(yy,3),xx,zz(2,yy),'r')
    title('YY (S_12)')
    
    
    subplot(2,3,3);
    plot(xx,A(yy,4),xx,zz(3,yy),'r')
    title('ZZ (S_13)')
    
    subplot(2,3,4);
    plot(xx,A(yy,5),xx,zz(4,yy),'r')
    title('ZX (S_33)')
    
    subplot(2,3,5);
    plot(xx,A(yy,6),xx,zz(5,yy),'r')
    title('ZY (S_44)')
    
    subplot(2,3,6);
    plot(xx,A(yy,7),xx,zz(6,yy),'r')
    title('XY (S_66)')
    
    %saveas(gcf, ['node', num2str(i), '_modulus'])
    %saveas(h,['node', num2str(i), '_modulus','.eps'],'eps')
end

matrix = zeros(6,6);
% first row of compliance matrix
matrix(1,1) = zz(1,1); % S_11
matrix(1,2) = zz(2,1); % S_12
matrix(1,3) = zz(3,1); % S_13

% second row of compliance matrix
matrix(2,1) = zz(2,1); % S_12
matrix(2,2) = zz(1,1); % S_11
matrix(2,3) = zz(3,1); % S_13

% third row of the compliance matrix
matrix(3,1) = zz(3,1); % S_13
matrix(3,2) = zz(3,1); % S_13
matrix(3,3) = zz(4,1); % S_33

% last three rows only have one element each
matrix(4,4) = zz(5,1); % S_44
matrix(5,5) = zz(5,1); % S_44
matrix(6,6) = zz(6,1); % S_66

stiff_mat = inv(matrix);
        
med_modulus = ones(6,m);
med_modulus(1,:) = med_modulus(1,:) * stiff_mat(1,1); % C_11
med_modulus(2,:) = med_modulus(2,:) * stiff_mat(1,2); % C_12
med_modulus(3,:) = med_modulus(3,:) * stiff_mat(1,3); % C_13
med_modulus(4,:) = med_modulus(4,:) * stiff_mat(3,3); % C_33
med_modulus(5,:) = med_modulus(5,:) * stiff_mat(4,4); % C_44
med_modulus(6,:) = med_modulus(6,:) * stiff_mat(6,6); % C_66


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Elastic Modulus %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = ls_size:1:m+ls_size-1;
    
    % Raw Elastic Modulus
    figure;
    subplot(2,3,1);
    plot(xx,A(yy,2),xx,med_modulus(1,yy))
    title('XX Elastic Modulus (C_11)')
    legend('every frame', 'median')
    
    subplot(2,3,2);
    plot(xx,A(yy,3),xx,med_modulus(2,yy))
    title('YY (C_12)')
    
    
    subplot(2,3,3);
    plot(xx,A(yy,4),xx,med_modulus(3,yy))
    title('ZZ (C_13)')
    
    subplot(2,3,4);
    plot(xx,A(yy,5),xx,med_modulus(4,yy))
    title('ZX (C_33)')
    
    subplot(2,3,5);
    plot(xx,A(yy,6),xx,med_modulus(5,yy))
    title('ZY (C_44)')
    
    subplot(2,3,6);
    plot(xx,A(yy,7),xx,med_modulus(6,yy))
    title('XY (C_66)')
    
    %saveas(gcf, ['node', num2str(i), '_modulus'])
    %saveas(h,['node', num2str(i), '_modulus','.eps'],'eps')
end


% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Take linear regression of stress and strain to compute engineering constants %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% reg_shear1 = lin_reg_str(6,1+ls_size:mx+ls_size) ./ lin_reg_def(6,1+ls_size:mx+ls_size) * .5; % G = 1/2 * stress[6] / strain[6]
% %figure;
% %plot(xx,reg_shear1)
% shear1 = median(reg_shear1);
% reg_shear2 = (lin_reg_str(4,1+ls_size:mx+ls_size) ./ lin_reg_def(4,1+ls_size:mx+ls_size) * .5 ...
%            +  lin_reg_str(5,1+ls_size:mx+ls_size) ./ lin_reg_def(5,1+ls_size:mx+ls_size) * .5) * .5; % G' = (1/2 * stress[4] / strain[4]
%                                                                                                      %     + 1/2 * stress[5] / strain[5]) * 1/2
%                                                                                                      % ie average G' for 4th and 5th component
% %plot(xx,reg_shear2)
% shear2 = median(reg_shear2);
% 
% % Compute v' and E'
% j = 10; % frames used to compute v' and E', and v and E
% k = 15;
% eng_mat2 = zeros(2,3);
% % first row
% eng_mat2(1,1) = -lin_reg_str(1,j) - lin_reg_str(2,j); % -stress[0] - stress[1]
% eng_mat2(1,2) = lin_reg_str(3,j);
% eng_mat2(1,3) = lin_reg_def(3,j);
% % second row
% eng_mat2(2,1) = -lin_reg_str(1,k) - lin_reg_str(2,k); % -stress[0] - stress[1]
% eng_mat2(2,2) = lin_reg_str(3,k);
% eng_mat2(1,3) = lin_reg_def(3,k);
% temp = rref(eng_mat2)
% young2 = 1 / temp(2,3)
% poisson2 = temp(1,3) / temp(2,3)
% 
% 
% % Compute v and E
% j = 1;
% k = 1;
% % first row is first equation of 1.2.35, first component of solution is 1/E, second component is v / E
% eng_mat2(1,1) =  lin_reg_str(1,j); %  stress[0]
% eng_mat2(1,2) = -lin_reg_str(2,j); % -stress[1]
% eng_mat2(1,3) =  lin_reg_def(1,j) + poisson2 / young2 * lin_reg_str(3,j);
% % second row is second equation of 1.2.35
% eng_mat2(2,1) =  lin_reg_str(2,k);
% eng_mat2(2,2) = -lin_reg_str(1,k);
% eng_mat2(2,3) =  lin_reg_def(1,k) + poisson2 / young2 * lin_reg_str(3,k);
% temp = rref(eng_mat2)
% young1 = 1 / temp(1,3)
% poisson1 = temp(2,3) / temp(1,3)
% 
% zz = ones(6,m);
% zz(1,:) = zz(1,:) * 1 / young1;           % S_11 = 1/E
% zz(2,:) = zz(2,:) * (-poisson1 / young1); % S_12 = -v/E
% zz(3,:) = zz(3,:) * (-poisson2 / young2); % S_13 = -v'/E'
% zz(4,:) = zz(4,:) * 1 / young2;           % S_33 = 1/E'
% zz(5,:) = zz(5,:) * 1 / shear2;           % S_44 = 1/G'
% zz(6,:) = zz(6,:) * 1 / shear1;           % S_66 = 1/G
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Compliance Matrix %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Name = ['node_comp_', num2str(i), '.txt'];
% if exist(Name, 'file')
%     
%     A=importdata(Name);
%     [m,n] = size(A); 
%     
%     figure;
%     subplot(2,3,1);
%     plot(xx,A(yy,2),xx,zz(1,yy),'r')
%     title('XX Compliance Matrix of reg')
%     legend('every step', 'median')
%     
%     subplot(2,3,2);
%     plot(xx,A(yy,3),xx,zz(2,yy),'r')
%     title('YY')
%     
%     
%     subplot(2,3,3);
%     plot(xx,A(yy,4),xx,zz(3,yy),'r')
%     title('ZZ')
%     
%     subplot(2,3,4);
%     plot(xx,A(yy,5),xx,zz(4,yy),'r')
%     title('ZX')
%     
%     subplot(2,3,5);
%     plot(xx,A(yy,6),xx,zz(5,yy),'r')
%     title('ZY')
%     
%     subplot(2,3,6);
%     plot(xx,A(yy,7),xx,zz(6,yy),'r')
%     title('XY')
%     
%     %saveas(gcf, ['node', num2str(i), '_modulus'])
%     %saveas(h,['node', num2str(i), '_modulus','.eps'],'eps')
% end
% 
% matrix = zeros(6,6);
% % first row of compliance matrix
% matrix(1,1) = zz(1,1); % S_11
% matrix(1,2) = zz(2,1); % S_12
% matrix(1,3) = zz(3,1); % S_13
% 
% % second row of compliance matrix
% matrix(2,1) = zz(2,1); % S_12
% matrix(2,2) = zz(1,1); % S_11
% matrix(2,3) = zz(3,1); % S_13
% 
% % third row of the compliance matrix
% matrix(3,1) = zz(3,1); % S_13
% matrix(3,2) = zz(3,1); % S_13
% matrix(3,3) = zz(4,1); % S_33
% 
% % last three rows only have one element each
% matrix(4,4) = zz(5,1); % S_44
% matrix(5,5) = zz(5,1); % S_44
% matrix(6,6) = zz(6,1); % S_66
% 
% stiff_mat = inv(matrix);
%         
% med_modulus = ones(6,m);
% med_modulus(1,:) = med_modulus(1,:) * stiff_mat(1,1); % C_11
% med_modulus(2,:) = med_modulus(2,:) * stiff_mat(1,2); % C_12
% med_modulus(3,:) = med_modulus(3,:) * stiff_mat(1,3); % C_13
% med_modulus(4,:) = med_modulus(4,:) * stiff_mat(3,3); % C_33
% med_modulus(5,:) = med_modulus(5,:) * stiff_mat(4,4); % C_44
% med_modulus(6,:) = med_modulus(6,:) * stiff_mat(6,6); % C_66
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Elastic Modulus %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Name = ['node', num2str(i), '.txt'];
% if exist(Name, 'file')
%     
%     A=importdata(Name);
%     [m,n] = size(A);
%     %xx = ls_size:1:m+ls_size-1;
%     
%     % Raw Elastic Modulus
%     figure;
%     subplot(2,3,1);
%     plot(xx,A(yy,2),xx,med_modulus(1,yy))
%     title('XX Elastic Modulus of reg')
%     legend('every frame', 'median')
%     
%     subplot(2,3,2);
%     plot(xx,A(yy,3),xx,med_modulus(2,yy))
%     title('YY')
%     
%     
%     subplot(2,3,3);
%     plot(xx,A(yy,4),xx,med_modulus(3,yy))
%     title('ZZ')
%     
%     subplot(2,3,4);
%     plot(xx,A(yy,5),xx,med_modulus(4,yy))
%     title('ZX')
%     
%     subplot(2,3,5);
%     plot(xx,A(yy,6),xx,med_modulus(5,yy))
%     title('ZY')
%     
%     subplot(2,3,6);
%     plot(xx,A(yy,7),xx,med_modulus(6,yy))
%     title('XY')
%     
%     %saveas(gcf, ['node', num2str(i), '_modulus'])
%     %saveas(h,['node', num2str(i), '_modulus','.eps'],'eps')
% end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Engineering Constants for isotropic material %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_eng_const_iso.txt'];
if exist(Name, 'file')
    
    A=importdata(Name);
    [m,n] = size(A);
    %xx = ls_size:1:m+ls_size-1;
    
    young1   = median(A(yy,2)); % E
    poisson1 = median(A(yy,3)); % v
    shear1   = median(A(yy,4)); % G from stress and strain
    shear2   = median(A(yy,5)); % G from G = E/(2+2v) 

    
    eng = ones(4,m);
    eng(1,:) = eng(1,:) * young1;
    eng(2,:) = eng(2,:) * poisson1;
    eng(3,:) = eng(3,:) * shear1;
    eng(4,:) = eng(4,:) * shear2;
    
%     zz = ones(6,m);
%     zz(1,:) = zz(1,:) * 1 / young1;           % S_11 = 1/E
%     zz(2,:) = zz(2,:) * (-poisson1 / young1); % S_12 = -v/E
%     zz(3,:) = zz(3,:) * (-poisson2 / young2); % S_13 = -v'/E'
%     zz(4,:) = zz(4,:) * 1 / young2;           % S_33 = 1/E'
%     zz(5,:) = zz(5,:) * 1 / shear2;           % S_44 = 1/G'
%     zz(6,:) = zz(6,:) * 1 / shear1;           % S_66 = 1/G
    
    figure;
    subplot(3,1,1);
    plot(xx,A(yy,2),xx,eng(1,yy))
    title('Youngs Mod (E)')

    
    subplot(3,1,2);
    plot(xx,A(yy,3),xx,eng(2,yy))
    title('Poisson ratio (v)')
    
    
    subplot(3,1,3);
    plot(xx,A(yy,4),'k',xx,eng(3,yy),'b',xx,A(yy,5),'r',xx,eng(4,yy),'g')
    title('Shear Mod (G)')
    legend('from stress/strain', 'stress/strain med', 'from G = E/(2+2v)', 'E/(2+2v) med')
    
    
    %saveas(gcf, ['node', num2str(i), '_strain'])
    %saveas(h,['node', num2str(i), '_strain','.eps'],'eps')
end


