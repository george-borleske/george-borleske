clear
close all

% Testnode is node 65
testnode = 65;

text = 'Equlibrium distances of backbone-backbone bond is always .35nm'
text = 'force_constant = k (1 - r_0 / r)'

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Positions of components of nodes 65 and 61 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(65), '.txt'];

A=importdata(Name);
[m,n] = size(A);
Name = ['Position_node_', num2str(61), '.txt'];
B=importdata(Name);
figure;
hold all
plot(1:m,(A(:,2)-B(:,2))/10,1:m,(A(:,3)-B(:,3))/10,1:m,(A(:,4)-B(:,4))/10)
title('Bond distance 65 to 61 in nanometers')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Bond between nodes 65 and 61 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['bond_', num2str(61), '_', num2str(65), '.dat'];
A=importdata(Name);
[m,n] = size(A);
plot(1:m,A(:,6))
legend('x', 'y', 'z', 'total distance')
figure;
plot(1:m,-A(:,3).*A(:,2),1:m,-A(:,4).*A(:,2),1:m,-A(:,5).*A(:,2))
title('Bond Forces between nodes 65 to 61')
legend('F_x^{65}', 'F_y^{65}', 'F_z^{65}')
figure;
plot(A(:,2))
title('Bond Force constant between nodes 65 and 61')




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Positions of components of nodes 65 and 61 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(65), '.txt'];

A=importdata(Name);
[m,n] = size(A);
Name = ['Position_node_', num2str(66), '.txt'];
B=importdata(Name);
figure;
hold all
plot(1:m,(A(:,2)-B(:,2))/10,1:m,(A(:,3)-B(:,3))/10,1:m,(A(:,4)-B(:,4))/10)
title('Bond distance 65 to 66 in nanometers')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Bond between nodes 65 and 61 %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['bond_', num2str(65), '_', num2str(66), '.dat'];
A=importdata(Name);
[m,n] = size(A);
plot(1:m,A(:,6))
legend('x', 'y', 'z', 'total distance')
figure;
plot(1:m,-A(:,3).*A(:,2),1:m,-A(:,4).*A(:,2),1:m,-A(:,5).*A(:,2))
title('Bond Forces between nodes 65 to 66')
legend('F_x^{65}', 'F_y^{65}', 'F_z^{65}')
figure;
plot(A(:,2))
title('Bond Force constant between nodes 65 and 66')

