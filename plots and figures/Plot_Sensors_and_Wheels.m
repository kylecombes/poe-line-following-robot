% % Plots Sensor and Wheel values on the same graph

%load sensor and wheel data first
clf
figure (1)
yyaxis left
plot(Time/1000, Lsensor,'g', 'LineWidth', 1.5);
hold on
plot(Time/1000, Rsensor, 'b', 'LineWidth', 1.5);
ylabel('Sensor Reading');

yyaxis right
plot(Time/1000, Lwheel, 'm', 'LineWidth', 1.5);
plot(Time/1000, Rwheel, 'r', 'LineWidth', 1.5);
ylabel('Wheel Speed')


xlabel('Time (seconds)');
title('Sensor and Wheel Data Over Time');
legend('Left Sensor', 'Right Sensor', 'Left Wheel', 'Right Wheel');