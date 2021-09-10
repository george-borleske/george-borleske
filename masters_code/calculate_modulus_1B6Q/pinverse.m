%close all
clear

node0 = 26;
node1 = 27;
node2 = 28;
node3 = 29;
node4 = 30;


dtensor = zeros(400,9);
etensor = zeros(400,9);
id3     = zeros(3,3); id3(1,1) = 1.0; id3(2,2) = 1.0; id3(3,3) = 1.0;

Name = ['Position_node_', num2str(node0), '.txt'];
if exist(Name, 'file')
    data0 = importdata(Name);
    [m,n] = size(data0);
end

Name = ['Position_node_', num2str(node1), '.txt'];
if exist(Name, 'file')
    data1 = importdata(Name);
    [m,n] = size(data1);
end

Name = ['Position_node_', num2str(node2), '.txt'];
if exist(Name, 'file')
    data2 = importdata(Name);
    [m,n] = size(data2);
end

Name = ['Position_node_', num2str(node3), '.txt'];
if exist(Name, 'file')
    data3 = importdata(Name);
    [m,n] = size(data3);
end

Name = ['Position_node_', num2str(node4), '.txt'];
if exist(Name, 'file')
    data4 = importdata(Name);
    [m,n] = size(data4);
end

for frame = 5:399,

frame

v   = zeros(3,4);
v_0 = zeros(3,4);

v(:,1) = data1(frame,2:4) - data0(frame,2:4);
v(:,2) = data2(frame,2:4) - data1(frame,2:4);
v(:,3) = data3(frame,2:4) - data2(frame,2:4);
v(:,4) = data4(frame,2:4) - data3(frame,2:4);

% Frame 5 is considered the initial frame
v_0(:,1) = data1(5,2:4) - data0(5,2:4);
v_0(:,2) = data2(5,2:4) - data1(5,2:4);
v_0(:,3) = data3(5,2:4) - data2(5,2:4);
v_0(:,4) = data4(5,2:4) - data3(5,2:4);

F = v * pinv(v_0);

E = 0.5*(F'*F - id3);

dtensor(frame,1) = F(1,1);
dtensor(frame,2) = F(1,2);
dtensor(frame,3) = F(1,3);

dtensor(frame,4) = F(2,1);
dtensor(frame,5) = F(2,2);
dtensor(frame,6) = F(2,3);

dtensor(frame,7) = F(3,1);
dtensor(frame,8) = F(3,2);
dtensor(frame,9) = F(3,3);

etensor(frame,1) = E(1,1);
etensor(frame,2) = E(1,2);
etensor(frame,3) = E(1,3);

etensor(frame,4) = E(2,1);
etensor(frame,5) = E(2,2);
etensor(frame,6) = E(2,3);

etensor(frame,7) = E(3,1);
etensor(frame,8) = E(3,2);
etensor(frame,9) = E(3,3);

end

A = dtensor(5:399,:);
    
    figure;

    subplot(3,3,1);
    plot(A(:,1))
    title('xx Deformation tensor')
    
    subplot(3,3,2);
    plot(A(:,2))
    title('xy')
    
    subplot(3,3,3);
    plot(A(:,3))
    title('xz')
    
    subplot(3,3,4);
    plot(A(:,4))
    title('yx')
    
    subplot(3,3,5);
    plot(A(:,5))
    title('yy')
    
    subplot(3,3,6);
    plot(A(:,6))
    title('yz')
    
    subplot(3,3,7);
    plot(A(:,7))
    title('zx')
    
    subplot(3,3,8);
    plot(A(:,8))
    title('zy')
    
    subplot(3,3,9);
    plot(A(:,9))
    title('zz')


A = etensor(5:399,:);
    figure;
    subplot(2,3,1);
    plot(A(:,1))
    title('xx Strain tensor')
   
    subplot(2,3,2);
    plot(A(:,5))
    title('yy')
    
    subplot(2,3,3);
    plot(A(:,9))
    title('zz')
    
    subplot(2,3,4);
    plot(A(:,3))
    title('zx')
   
    subplot(2,3,5);
    plot(A(:,6))
    title('zy')
    
    subplot(2,3,6);
    plot(A(:,2))
    title('xy')
    
