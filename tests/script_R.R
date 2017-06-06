
for (i in 1:nrow(ACS) ) {
  ACS_res[i,1] <- min(ACS[i, 2:ncol(ACS)])
}
colnames(ACS_res)[1] = "min"
for (i in 1:nrow(ACS) ) {
  ACS_res[i,2] <- max(ACS[i, 2:ncol(ACS)])
}
colnames(ACS_res)[2] = "max"
for (i in 1:nrow(ACS) ) {
  ACS_res[i,3] <- mean(unlist(ACS[i, 2:ncol(ACS)]))
}
colnames(ACS_res)[3] = "mean"
for (i in 1:nrow(ACS) ) {
  ACS_res[i,4] <- sd(unlist(ACS[i, 2:ncol(ACS)]))
}
colnames(ACS_res)[4] = "sd"
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
