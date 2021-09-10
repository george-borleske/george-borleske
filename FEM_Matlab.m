% A basic Finite Element Implemenation for approximating: 
% f(x,y) = sin(pi*x)*sin(pi*y) on the domain [0,1] x [0,1]

close all
clear all


n  = 8;      % decide how fine the mesh is
dx = 1 / n;  % x length of an element
dy = 1 / n;  % y length of an element
nx = 0:dx:1; % number of elements in the x direction
ny = 0:dy:1; % number of elements in the y direction
h = dx;      % side length of an element (they are rectangles/squares)

num_node = length(nx) * length(ny); % total number of nodes
num_rec = (length(nx) - 1)^2;       % total number of rectangles
num_tri = (length(nx) - 1)^2*2;     % total number of triangles (2x tri per rec)

% Store the cordinates of the nodes
x_pos = zeros(num_node,1);
y_pos = zeros(num_node,1);
count = 1;
for i = 0:dx:1
    for j = 0:dy:1
        x_pos(count) = i;
        y_pos(count) = j;
        count = count + 1;
    end
end

% Store the which nodes are on each triangle
% Goes rectangle by rectangle
tri = zeros(num_tri,3);
rec = zeros(num_rec,4);
for i = 1:num_rec
    for i = 1:num_rec
        % Counter Clockwise orientation
        rec(i,1) = i + floor((i-1)/n);
        rec(i,4) = i + 1 + floor((i-1)/n);
        rec(i,2) = i + n + 1 + floor((i-1)/n);
        rec(i,3) = i + n + 2 + floor((i-1)/n);
        tri(2*i-1,1) = rec(i,1);
        tri(2*i-1,2) = rec(i,2);
        tri(2*i-1,3) = rec(i,4);
        tri(2*i,1) = rec(i,2);
        tri(2*i,2) = rec(i,3);
        tri(2*i,3) = rec(i,4);
    end
end

% Compute the area of each triangle
A_tri = zeros(num_tri,1);
for i = 1:num_tri
    % 1/2 x s1 x s2 = is area of triangle
    % where s1 and s2 are vectors of two sides of the triangle
    s1 = [x_pos(tri(i,2)) - x_pos(tri(i,1)), y_pos(tri(i,2)) - y_pos(tri(i,1))];
    s2 = [x_pos(tri(i,3)) - x_pos(tri(i,1)), y_pos(tri(i,3)) - y_pos(tri(i,1))];
    A_tri(i) = .5 * abs(s1(1) * s2(2) - s2(1) * s1(2));
end


% Find if nodes are on the boundary
bound = zeros(num_node,1);
tol = 0.0000001; 
for i = 1:num_node
   if(abs(x_pos(i)-1) <= tol || abs(x_pos(i)) <= tol) % far left or far right of domain
       bound(i) = 1; % 1 indicates boundary. 0 indicates interior node
   end
   if(abs(y_pos(i)-1) <= tol || abs(y_pos(i)) <= tol) % top and bottom of the domain
       bound(i) = 1;
   end
end

% Check for correct boundary nodes
figure
title('boundary node check')
hold on
for i = 1:num_node
   if(bound(i) == 1)
       scatter(x_pos(i),y_pos(i))
   end
end
hold off

% Compute the Global and Elemental Stiffness Matrix
ele_A = zeros(3,3); % Element Stiffness Matrix
glob_A = zeros(num_node,num_node); % Global Stiffness Matrix
% Loop through the triangles
for k = 1:num_tri
   grad_phi1 = [x_pos(tri(k,2)) -  x_pos(tri(k,1)), y_pos(tri(k,1)) -  y_pos(tri(k,2))];
   grad_phi2 = [x_pos(tri(k,1)) -  x_pos(tri(k,3)), y_pos(tri(k,3)) -  y_pos(tri(k,1))];
   grad_phi3 = [x_pos(tri(k,3)) -  x_pos(tri(k,2)), y_pos(tri(k,2)) -  y_pos(tri(k,3))];
   
   ele_A(1,1) = norm(grad_phi3)^2;
   ele_A(1,2) = grad_phi3(2) * grad_phi2(2) + grad_phi3(1) * grad_phi2(1);
   ele_A(1,3) = grad_phi3(2) * grad_phi1(2) + grad_phi3(1) * grad_phi1(1);
   
   ele_A(2,1) = grad_phi3(2) * grad_phi2(2) + grad_phi3(1) * grad_phi2(1);
   ele_A(2,2) = norm(grad_phi2)^2;
   ele_A(2,3) = grad_phi1(2) * grad_phi2(2) + grad_phi1(1) * grad_phi2(1);
   
   ele_A(3,1) = grad_phi3(2) * grad_phi1(2) + grad_phi3(1) * grad_phi1(1);
   ele_A(3,2) = grad_phi1(2) * grad_phi2(2) + grad_phi1(1) * grad_phi2(1);
   ele_A(3,3) = norm(grad_phi1)^2;
   
   ele_A = ele_A / (4 * A_tri(k));
   
   % Diagonal of element matrix
   for i = 1:3
       % row and column of the global stiffness matrix A
       row = tri(k,i);
       col = tri(k,i);
       if(bound(row) == 0)
           glob_A(row,col) = glob_A(row,col) + ele_A(i,i);
       end
   end
   
   row = tri(k,1);
   col = tri(k,2);
   if(bound(row) == 0)
       glob_A(row,col) = glob_A(row,col) + ele_A(1,2);
   end
   if(bound(col) == 0)
       glob_A(col,row) = glob_A(col,row) + ele_A(2,1);
   end
   
   row = tri(k,1);
   col = tri(k,3);
   if(bound(row) == 0)
       glob_A(row,col) = glob_A(row,col) + ele_A(1,3);
   end
   if(bound(col) == 0)
       glob_A(col,row) = glob_A(col,row) + ele_A(3,1);
   end
   
   row = tri(k,2);
   col = tri(k,3);
   if(bound(row) == 0)
       glob_A(row,col) = glob_A(row,col) + ele_A(2,3);
   end
   if(bound(col) == 0)
       glob_A(col,row) = glob_A(col,row) + ele_A(3,2);
   end
end

% Put one's on the diagonal of glob_A where that node is on the boundary of the domain
for i = 1:num_node
    if(bound(i) == 1)
        glob_A(i,i) = 1;
    end
end

% Compute the integral of f*v
glob_f   = zeros(num_node,1);
num_quad = 3;
quad     = zeros(2,1);         % gaussian quadrature point, x and y coords
quad_tri = [4/6 1/6 1/6 1/3;
            1/6 4/6 1/6 1/3;
            1/6 1/6 4/6 1/3];

% Loop through the triangles
for i = 1:num_tri
    x1 = x_pos(tri(i,1));
    x2 = x_pos(tri(i,2));
    x3 = x_pos(tri(i,3));
    y1 = y_pos(tri(i,1));
    y2 = y_pos(tri(i,2));
    y3 = y_pos(tri(i,3));
    
    % Loop through the quadrature points
    for j = 1:num_quad
        quad(1) = quad_tri(j,1)*x1 + quad_tri(j,2)*x2 + quad_tri(j,3)*x3;
        quad(2) = quad_tri(j,1)*y1 + quad_tri(j,2)*y2 + quad_tri(j,3)*y3;
        
        phi1x = (y2-y3) / A_tri(i);
        phi2x = (y3-y1) / A_tri(i);
        phi3x = (y1-y2) / A_tri(i);
        
        phi1y = (x3-x2) / A_tri(i);
        phi2y = (x1-x3) / A_tri(i);
        phi3y = (x2-x1) / A_tri(i);
        
        gradux = pi * cos(pi*quad(1)) * sin(pi*quad(2)); 
        graduy = pi * sin(pi*quad(1)) * cos(pi*quad(2));
        
        glob_f(tri(i,1)) = glob_f(tri(i,1)) + .5 * A_tri(i) * quad_tri(j,4) * (gradux*phi1x + graduy*phi1y);
        glob_f(tri(i,2)) = glob_f(tri(i,2)) + .5 * A_tri(i) * quad_tri(j,4) * (gradux*phi2x + graduy*phi2y);
        glob_f(tri(i,3)) = glob_f(tri(i,3)) + .5 * A_tri(i) * quad_tri(j,4) * (gradux*phi3x + graduy*phi3y);
    end
end


% Set Dirichlet boundary conditions
for i = 1:num_node
    if(bound(i) == 1)
        glob_f(i) = pi * sin(pi * x_pos(i)) * sin(pi * y_pos(i));
    end
end

soln = glob_A\glob_f;

% Compute the exact solution for comparision
exact_soln = zeros(num_node,1);
for i = 1:num_node
    exact_soln(i) = sin(pi * x_pos(i)) * sin(pi * y_pos(i));
end
exact_soln;


figure
trimesh(tri,x_pos,y_pos,soln)
title('FEM solution')

figure
trimesh(tri,x_pos,y_pos,exact_soln)
title('Exact Solution')

error = zeros(num_tri,1);
for i = 1:num_tri
    x1 = x_pos(tri(i,1));
    x2 = x_pos(tri(i,2));
    x3 = x_pos(tri(i,3));
    y1 = y_pos(tri(i,1));
    y2 = y_pos(tri(i,2));
    y3 = y_pos(tri(i,3));
    
    
    for j = 1:num_quad
        quad(1) = quad_tri(j,1)*x1 + quad_tri(j,2)*x2 + quad_tri(j,3)*x3;
        quad(2) = quad_tri(j,1)*y1 + quad_tri(j,2)*y2 + quad_tri(j,3)*y3;
        
        area1 = 0.5*((x2-quad(1)) * (y3-quad(2)) - (x3-quad(1)) * (y2-quad(2)));
        area2 = 0.5*((quad(1)-x1) * (y3-y1) - (x3-x1) * (quad(2)-y1));
        area3 = 0.5*((x2-x1) * (quad(2)-y1) - (quad(1)-x1) * (y2-y1));
        
        coef1 = area1/A_tri(i);
        coef2 = area2/A_tri(i);
        coef3 = area3/A_tri(i);
        
        
        numerical = coef1 * soln(tri(i,1)) + coef2 * soln(tri(i,2)) ...
            + coef3 * soln(tri(i,3));
        exact     = sin(pi * quad(1)) * sin(pi * quad(2));
        
        diff = exact - numerical;
        error(i) = error(i) + quad_tri(j,4) * diff^2;
    end
end

L2err = sqrt(sum(error.*A_tri))