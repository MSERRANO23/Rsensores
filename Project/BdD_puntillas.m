clear;
clc;

fid = fopen("BdD_puntillas5.csv",'wt');
for i=1:10
    switch i
        case 1
            fileID = fopen('datos_p1.txt','r');
        case 2
            fileID = fopen('datos_p2.txt','r');
        case 3
            fileID = fopen('datos_p3.txt','r');
        case 4
            fileID = fopen('datos_p4.txt','r');
        case 5
            fileID = fopen('datos_p5.txt','r');
        case 6
            fileID = fopen('datos_p6.txt','r');
        case 7
            fileID = fopen('datos_p7.txt','r');
        case 8
            fileID = fopen('datos_p8.txt','r');
        case 9
            fileID = fopen('datos_p9.txt','r');
        case 10
            fileID = fopen('datos_p10.txt','r');
    end

    p_10 = fscanf(fileID,'%f',Inf);
    fclose(fileID);

    p10 = transpose(p_10);

    p10_x = p10(1:3:end);
    p10_y = p10(2:3:end);
    p10_z = p10(3:3:end);

    % Acelerometro

    % EJE X
    if i == 5
        p10_x_acel = p10_x(1:3:end-1);
    else
        p10_x_acel = p10_x(1:3:end);
    end

    % EJE Y
    p10_y_acel = p10_z(1:3:end);

    % EJE Z
    p10_z_acel =  -1.*p10_y(1:3:end);
    

    % Giroscopio
    % EJE X
    p10_x_giro = -1.*p10_x(2:3:end);

    % EJE Y
    if i == 9
        p10_y_giro = [p10_z(2:3:end), repelem(p10_z(2:3:end),2)];
    else
        p10_y_giro = p10_z(2:3:end);
    end
    
    % EJE Z
    p10_z_giro = p10_y(2:3:end);
    
    % MAGNETOMETRO
    % EJE X
    if i == 6 || i == 9
        p10_x_magn = [p10_x(3:3:end),repelem(p10_x(end), 2)];
    else
        p10_x_magn = p10_x(3:3:end);
    end

    % EJE Y
    if i == 6 || i == 9
        p10_y_magn = [p10_y(3:3:end),repelem(p10_y(end), 2)];
    else
        p10_y_magn = p10_y(3:3:end);
    end

    % EJE Z
    if i == 1 || i == 3 || i == 6 || i == 9 || i == 10
        p10_z_magn = [p10_z(3:3:end), repelem(p10_z(end),2)];
    else
        p10_z_magn = p10_z(3:3:end);
    end

    fprintf(fid,'Numero de medición |     Eje x     |     Eje y     |     Eje z     |     Eje x     |     Eje y     |     Eje z     |     Eje x     |     Eje y     |     Eje z     |\n');
    for j = 1:length(p10_x_acel)
        fprintf(fid,'%d,', j);
        fprintf(fid,' %f,', p10_x_acel(j));
        fprintf(fid,'%f,', p10_y_acel(j));
        fprintf(fid,'%f,', p10_z_acel(j));
        fprintf(fid,' ,');
        fprintf(fid,'%f,', p10_x_giro(j));
        fprintf(fid,'%f,', p10_y_giro(j));
        fprintf(fid,'%f,', p10_z_giro(j));
        fprintf(fid,' ,');
        fprintf(fid,'%f,', p10_x_magn(j));
        fprintf(fid,'%f,', p10_y_magn(j));
        fprintf(fid,'%f,\n', p10_z_magn(j));
    end

    fprintf(fid, '\n\n\n');
end

fclose(fid);