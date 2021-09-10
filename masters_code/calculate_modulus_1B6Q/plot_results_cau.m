clear
close all
nodes = 120;


ls_size = 20;
start   = 1; 
last    = 399;
xx2     = start:last;         % frames for stress and strain
xx      = start+ls_size:last; % frames of interest for compliance matrix,
                              % young's modulus, and engineering constants
                              
first_alpha = 7;
last_alpha  = 49;
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


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stress %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['node', num2str(i), '_stress_cau.txt'];
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


