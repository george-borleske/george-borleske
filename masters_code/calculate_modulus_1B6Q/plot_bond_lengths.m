close all
clear

plot_para = 1;  % 1 plots total bond length, 2 plots x component, 3 plots y component, 4 plots z component
start     = 1; % First node of the interest for the bond lengths
last      = 37; % Last node of interest for the bond lengths


leg_count = 1;  % Keeps track so a max of 6 bond lengths are plotted on any given figure
leg_bonds = []; % Stores legend for each bond
leg_start = 0;  % First node in a bond
leg_end   = 0;  % Second node in a bond

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Position of first node of alpha helix %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Name = ['Position_node_', num2str(start), '.txt'];
if exist(Name, 'file')
    A=importdata(Name);
    [m,n] = size(A);
    B = A;
    leg_count = leg_count + 1;
    leg_end  = start;
else
    disp('can''t find first bond')
    return
end
C = zeros(1,m);
figure;
hold on

for j = start+1:last
    Name = ['Position_node_', num2str(j), '.txt'];
    if exist(Name, 'file')
        j
        A=importdata(Name);
        [m,n] = size(A);
        for i = 1:m
            if plot_para == 1
                C(i) = norm(A(i,2:4) - B(i,2:4));
            elseif plot_para == 2
                C(i) = B(i,2) - A(i,2);
            elseif plot_para == 3
                C(i) = abs(B(i,3) - A(i,3));
            elseif plot_para == 4
                C(i) = abs(B(i,4) - A(i,4));
            else
                error = 'something went wrong plotting'
            end
        end
        plot(C)
        B = A;
        
        leg_count = leg_count + 1;
        leg_start = leg_end;
        leg_end   = j;
        if(leg_end < 10)
            leg_bonds = [leg_bonds; [num2str(0), num2str(0), num2str(leg_start), '-', num2str(0), num2str(0), num2str(leg_end)]];
        else if (leg_end > 9 && leg_start < 10)
                leg_bonds = [leg_bonds; [num2str(0), num2str(0), num2str(leg_start), '-', num2str(0), num2str(leg_end)]];
            else if(leg_end < 100)
                    leg_bonds = [leg_bonds; [num2str(0), num2str(leg_start), '-', num2str(0), num2str(leg_end)]];
                else if(leg_end > 99 && leg_start < 100)
                        leg_bonds = [leg_bonds; [num2str(0), num2str(leg_start), '-', num2str(leg_end)]];
                    else if(leg_start > 99)
                            leg_bonds = [leg_bonds; [num2str(leg_start), '-', num2str(leg_end)]];
                        else
                            disp('Error in legend')
                            return
                        end
                    end
                end
            end
        end
        
        if(leg_count == 7)
            legend(leg_bonds);
            hold off
            figure;
            hold on
            leg_count = 1;
            leg_bonds = [];
            if plot_para == 2
                title('x-component of Bond lengths')
            elseif plot_para == 1
                title('Total Bond lengths')
            elseif plot_para == 3
                title('absolute value of y-component of Bond lengths')
            elseif plot_para == 4
                title('absolute value of z-component of Bond lengths')
            else
                error = 'something went wrong titling plot'
            end
        end
    end
    if(j == last)
        legend(leg_bonds);
    end
end
        
