%Comunicacion UART

clear all; 
puerto = input("Puerto COM: ", "s"); 
conexion = serialport(puerto, 4800); 
muestras = 1000;
h = animatedline;
axis ([0 muestras 0 3.3])
x = linspace (0,1,muestras);

%Grafica
figure("Name", "ADC");
title("ADC","fontsize",14);
xlabel("tiempo","fontsize",12);
ylabel("voltaje","fontsize",12);
grid on;

%graficar
for limite = 1:muestras
    lectura = str2double(readline(conexion));
    signal = (lectura*3.3)/4095;
    addpoints(h,x(muestras),signal)
    drawnow
end 