for (i in 1:nrow(ACS) ) {
  MaxMinLS_res[i,2] <- min(MaxMinLS[i, 2:ncol(ACS)])
}
colnames(MaxMinLS_res)[1] = "instance"
colnames(MaxMinLS_res)[2] = "min"
for (i in 1:nrow(ACS) ) {
  MaxMinLS_res[i,3] <- max(MaxMinLS[i, 2:ncol(ACS)])
}
for (i in 1:nrow(ACS) ) {
  MaxMinLS_res[i,4] <- mean(unlist(MaxMinLS[i, 2:ncol(ACS)]))
}
colnames(MaxMinLS_res)[4] = "mean"
for (i in 1:nrow(ACS) ) {
  MaxMinLS_res[i,5] <- sd(unlist(MaxMinLS[i, 2:ncol(ACS)]))
}
colnames(MaxMinLS_res)[5] = "sd"
ACS_res <- cbind(ACS[,1], ACS_res)
colnames(ACS_res)[1] = "instance"

MaxMin_res <- MaxMin[,1]
MaxMin_res <- as.data.frame(MaxMin_res)

for (i in 1:nrow(MaxMin) ) {
  MaxMin_res[i,2] <- min(MaxMin[i, 2:ncol(MaxMin)])
}
colnames(MaxMin_res)[2] = "min"

for (i in 1:nrow(MaxMin) ) {
  MaxMin_res[i,3] <- max(MaxMin[i, 2:ncol(MaxMin)])
}
colnames(MaxMin_res)[3] = "max"

for (i in 1:nrow(MaxMin) ) {
  MaxMin_res[i,4] <- mean(unlist(MaxMin[i, 2:ncol(MaxMin)]))
}
colnames(MaxMin_res)[4] = "mean"

for (i in 1:nrow(MaxMin) ) {
  MaxMin_res[i,5] <- sd(unlist(MaxMin[i, 2:ncol(MaxMin)]))
}
colnames(MaxMin_res)[5] = "sd"

write.table(MaxMin_res, file="Max_Min_Ant_System-results.csv", quote=F, row.names=F, sep=";")
write.table(ACS_res, "Ant_Colony_System-results.csv", quote=F, row.names=F, sep=";")


plot(x = unlist(rpd_comp[1:5,2]),
     y = unlist(rpd_comp[1:5,3]),
     main="rpd correlation",
     xlab="MMAS rpd",
     ylab="ACS rpd",
     col="red",
     xlim=c(0, 1.2),
     ylim=c(0, 1.2),
     pch=4)

points(x=unlist(rpd_comp[6:11,2]), unlist(rpd_comp[6:11,3]), col="blue", pch=4)
points(x=unlist(rpd_comp[12:16,2]), unlist(rpd_comp[12:16,3]), col="green", pch=4)

legend("bottomright", inset=.05, 
       title="Number of characters",
       c("20","2", "4"),
       fill=c("blue", "red", "green"),
       horiz=FALSE)

cor(x = unlist(rpd_comp[,2]), y = unlist(rpd_comp[,3]))
cor.test(x = unlist(rpd_comp[,2]), y = unlist(rpd_comp[,3]), method="spearman")$p.value

# convergence
conv_ACS1 <- read.csv("Convergence/2-30-10000-1-9-ACS", sep=";")
conv_MaxMin1 <- read.csv("Convergence/2-30-10000-1-9-MaxMin", sep=";")

conv_ACS2 <- read.csv("Convergence/20-10-10000-1-9-ACS", sep=";")
conv_MaxMin2 <- read.csv("Convergence/20-10-10000-1-9-MaxMin", sep=";")

conv_ACS1 <- cbind(conv_ACS1, (conv_ACS1[,2]-4278)/4278)
conv_MaxMin1 <- cbind(conv_MaxMin1, (conv_MaxMin1[,2]-4278)/4278)

plot(x = conv_ACS1[,1],
     y = conv_ACS1[,3],
     main="Convergence on 2-30-10000-1-9",
     xlab="Number of evaluations",
     ylab="Relative Percentage Deviation",
     col="red",
     xlim=c(0, 12410),
     ylim=c(0, 0.03),
     pch=4,
     type='l')

lines(x=conv_MaxMin1[,1], y=conv_MaxMin1[,3], col="blue", pch=4)

legend("topright", inset=.05, 
       title="Algorithm",
       c("Ant Colony System","Max Min Ant System"),
       fill=c("red", "blue"),
       horiz=FALSE)

conv_ACS2 <- cbind(conv_ACS2, (conv_ACS2[,2]-7825)/7825)
conv_MaxMin2 <- cbind(conv_MaxMin2, (conv_MaxMin2[,2]-7825)/7825)

plot(x = conv_ACS2[,1],
     y = conv_ACS2[,3],
     main="Convergence on 20-10-10000-1-9",
     xlab="Number of evaluations",
     ylab="Relative Percentage Deviation",
     col="red",
     xlim=c(0, 6186),
     ylim=c(0, 0.007),
     pch=4,
     type='l')

lines(x=conv_MaxMin2[,1], y=conv_MaxMin2[,3], col="blue", pch=4)

legend("topright", inset=.05, 
       title="Algorithm",
       c("Ant Colony System","Max Min Ant System"),
       fill=c("red", "blue"),
       horiz=FALSE)

