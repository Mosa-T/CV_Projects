# Mosa thoukwho - 311590707

# Big data final project

## Main subject ##

# Examination of possible correlation between student performance in Portuguese language classes and the student’s socioeconomic status


# Main sources:
# https://ggplot2.tidyverse.org/reference/geom_density.html
# https://rstudio-pubs-static.s3.amazonaws.com/446972_323b4475ff0749228fe4057c4d7685f5.html#book-method
# https://www.rdocumentation.org/packages/caret/versions/6.0-88/topics/varImp
# https://towardsdatascience.com/how-to-create-a-correlation-matrix-with-too-many-variables-309cc0c0a57
# https://cran.r-project.org/web/packages/FactoMineR/FactoMineR.pdf page 21
# https://www.rdocumentation.org/packages/stats/versions/3.6.2/topics/model.matrix
# https://rpubs.com/Mentors_Ubiqum/tunegrid_tunelength
# https://csantill.github.io/RTuningModelParameters/
# https://machinelearningmastery.com/tune-machine-learning-algorithms-in-r/
# https://rpubs.com/coleeagland/decisiontreesislr833
# https://en.wikipedia.org/wiki/Root-mean-square_deviation


# Packages

list.of.packages <- c("dplyr","ggplot2","caret","tidyr","FactoMineR","Hmisc","corrplot","psych",
                      "randomForest","rpart","rpart.plot","DAAG","tidyr")
#
# You should be able to simply reuse the following lines of code as is
#
new.packages <- list.of.packages[!(list.of.packages %in% installed.packages()[,"Package"])]
#
if(length(new.packages)) install.packages(new.packages)
#
# By now we have installed the requisite packages. Time to load them .
#
lapply(list.of.packages,function(x){library(x,character.only=TRUE)})
#
# Ready to go
#

#Read data
dt <- read.table('student-por.csv', header = TRUE, sep = ';',stringsAsFactors = TRUE)
#remove reason and failure as one is not relevant and the other is reflected in the student's G1,G2,G3 so it's redundant
dt<-dt[,-c(11,15)]
#remove G1 and G2 as we'll looking at the overall, which is G3
dt<-dt[,-c(29,30)]



GP<-filter(dt,school == 'GP')
MS<-filter(dt,school == 'MS')
var.test(GP$G3,MS$G3)
#p<0.5 run Welch t -statistic
t.test(GP$G3,MS$G3,car.equal=FALSE)


#########################Histogram - Distribution of grades.#########################
ggplot2::ggplot(dt,aes(x=G3)) + geom_histogram()

#########################linear models - Grades by different variables#########################

ggplot(dt,aes(Medu,G3))+
  geom_smooth(method = lm,colour="darkred")+
  ggtitle("linear mode - grade by Medu")

ggplot(dt,aes(Fedu,G3))+
  geom_smooth(method = lm,colour="darkred")+
  ggtitle("linear mode - grade by Fedu")

ggplot(dt,aes(famrel,G3))+
  geom_smooth(method = lm,colour="darkred")+
  ggtitle("linear mode - grade by famrel")

ggplot(dt,aes(traveltime,G3))+
  geom_smooth(method = lm,colour="darkred")+
  ggtitle("linear mode - grade by traveltime")

ggplot(dt,aes(studytime,G3))+
  geom_smooth(method = lm,colour="darkred")+
  ggtitle("linear mode - grade by studytime")


#########################boxplots - Grades by different variables#########################

ggplot(dt,aes(school,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(address,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(Mjob,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(Fjob,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(famsize,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(Pstatus,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(guardian,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(schoolsup,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

ggplot(dt,aes(famsup,G3))+geom_point(alpha = 0.3) +
  geom_boxplot(alpha = 0, colour = "black")

#########################Geom_density - Grades by different variables#########################

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=address), size = 2) +
  ggtitle("Grade density by address")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=Mjob), size= 2) +
  ggtitle("Grade density by mother's job")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=Fjob),size = 2) +
  ggtitle("Grade density by father's job")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(traveltime)),size = 2) +
  ggtitle("Grade density by travel time")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(studytime)),size = 2) +
  ggtitle("Grade density by study time")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=famsize),size = 2) +
  ggtitle("Grade density by family size")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=school), size = 2) +
  ggtitle("Grade density by school")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(Medu)),size = 2) +
  ggtitle("Grade density by mother's education")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(Fedu)),size = 2) +
  ggtitle("Grade density by father's education")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(famrel)),size = 2) +
  ggtitle("Grade density by family relationships")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(famsup)),size = 2) +
  ggtitle("Grade density by family support")

ggplot(dt, aes(x=G3)) +
  geom_density(aes(color=as.factor(Dalc)), size = 2) +
  ggtitle("Grade density by Dalc")

#########################correlations between all data variables.#########################

corr_simple <- function(data=df,sig=0.5){
  #convert data to numeric in order to run correlations
  #convert to factor first to keep the integrity of the data - each value will become a number rather than turn into NA
  df_cor <- data %>% mutate_if(is.character, as.factor)
  df_cor <- df_cor %>% mutate_if(is.factor, as.numeric)  #run a correlation and drop the insignificant ones
  corr <- cor(df_cor)
  #prepare to drop duplicates and correlations of 1
  corr[lower.tri(corr,diag=TRUE)] <- NA
  #drop perfect correlations
  corr[corr == 1] <- NA   #turn into a 3-column table
  corr <- as.data.frame(as.table(corr))
  #remove the NA values from above
  corr <- na.omit(corr)   #select significant values
  corr <- subset(corr, abs(Freq) > sig)
  #sort by highest correlation
  corr <- corr[order(-abs(corr$Freq)),]   #print table
  print(corr)  #turn corr back into matrix in order to plot with corrplot
  mtx_corr <- reshape2::acast(corr, Var1~Var2, value.var="Freq")

  #plot correlations visually
  corrplot(mtx_corr, is.corr=FALSE, tl.col="black", na.label=" ")
}
#0.2 for low positive correlations
#Note Strong correlation of G1-G3 with studytime, higher, Medu and Fedu(specifically ones with jobs as teachers).
corr_simple(dt,0.2)


#########################multiple variables linear model.#########################

lm_model_dt <- lm(G3 ~.,data=dt)
lm_summary_dt <- summary(lm_model_dt)
r_sq<-lm_summary_dt$r.squared
pval<-lm_summary_dt$coefficients
plot(lm_model_dt$coefficients)





#########################Principal component analysis.#########################

dt.pca <- dt
dt.pca <- dt.pca %>% mutate_if(is.character, as.factor)
dt.pca <- dt.pca %>% mutate_if(is.factor, as.numeric)

ncpest<-estim_ncp(dt.pca,scale=TRUE,method="GCV")$ncp
dt.pca <- PCA(dt.pca, scale.unit=TRUE, ncp=ncpest, graph=F)

dt.pca$eig
print(dt.pca$var$contrib)

#screeplot
barplot(dt.pca$eig[, 2],
        names.arg=1:nrow(dt.pca$eig),
        main = "Variances",
        xlab = "Principal Components",
        ylab = "Percentage of variances",
        col ="steelblue")
# Add connected line segments to the plot
lines(x = 1:nrow(dt.pca$eig), dt.pca$eig[, 2], type="b", pch=19, col = "red")

plot.PCA(dt.pca, axes=c(1, 2), choix="varcor", habillage='contrib',autoLab="auto",cex=0.9)
pcadims<-dimdesc(dt.pca,axes=c(1:ncpest))

for(i in 1:ncpest){
  print(pcadims[i])
}



######################### Model. #########################

#We take the variables from the dimensions that are considered the best dimensions by estim_ncp()
#remove school,age,sex as they seem less relevant to us right now
namesC<-unique(rownames(pcadims$Dim.1$quanti),rownames(pcadims$Dim.2$quanti))
namesC<- namesC[!(namesC %in% c('school','age','sex'))]
dt_set <- dt[,colnames(dt) %in% namesC]


#expand the variables in case there are multiple choices that can have extreme cases that can help us determine more easily
dt_set<-data.frame(model.matrix(~.,dt_set))
dt_set$X.Intercept.<-NULL
dt_set <- dt_set %>% mutate_if(is.character, as.factor)
dt_set <- dt_set %>% mutate_if(is.factor, as.numeric)

#set up training and test sets
trainTestSet<-sort(sample(nrow(dt_set),nrow(dt_set)*.7))
trainSet<-dt_set[trainTestSet,]
testSet<-dt_set[-trainTestSet,]


rmse_func <- function(model_obj, testing = NULL, target = NULL) {
  yhat <- predict(model_obj, newdata = testing)
  actual <- testing[[target]]
  sqrt(mean((yhat-actual)^2))
}


#Decision Tree

rtree_model<-rpart(G3~.,data=trainSet,method  = "anova",
                   control = rpart.control(minsplit = 8, maxdepth = 14,cp = 0.01))
rtree_prediction<-predict(rtree_model,testSet)
rpart.plot(rtree_model)

#sum<-summary(rtree_model)
#sum$variable.importance

varImp(rtree_model)
rmse_func(rtree_model,testSet,"G3")



#bagging


rctrl1 <- trainControl(method = "cv", number = 10)

tbag_model <- train(G3 ~ ., data = trainSet,
                    method = "treebag",
                    trControl = rctrl1,
                    preProc = c("center", "scale"),
                    nbagg = 10)

tb_pred = predict(tbag_model,testSet)

plotty = data.frame(testing = testSet$G3,prediction = tb_pred)
print(ggplot(plotty, aes(x=testing, y=prediction)) + xlab("testSet") + ylab("prediction") +
        geom_point(size=3, colour="red", alpha=0.9) + geom_point(size=1, colour="black", alpha=0.9) +
        theme(plot.title = element_text(hjust = 0.5)) + ggtitle("testSet & prediction"))




varImp(tbag_model)

rmse_func(tbag_model,testSet,"G3")


#Random Forest

control <- trainControl(method="repeatedcv", number=10, repeats=3, search="grid")

tunegrid <- expand.grid(.mtry=c(1:15))

rf_model <- train(G3~., data=trainSet, method="rf", metric="RMSE", tuneGrid=tunegrid, trControl=control)

rf_pred = predict(rf_model,testSet)

varImp(rf_model)

plotty = data.frame(testing = testSet$G3,prediction = rf_pred)
print(ggplot(plotty, aes(x=testing, y=prediction)) + xlab("testSet") + ylab("prediction") +
        geom_point(size=3, colour="red", alpha=0.9) + geom_point(size=1, colour="black", alpha=0.9) +
        theme(plot.title = element_text(hjust = 0.5)) + ggtitle("testSet & prediction"))


rmse_func(rf_model,testSet,"G3")



#Random Forest with PCA

pcaThing = prcomp(trainSet,scale. = T,center = T)

summary(pcaThing)
#70%-80% cumulative proportion usually falls around PC19 and above which is what we're going for.
trainingPca = data.frame(cbind(pcaThing$x[,1:19],G3=trainSet$G3))

rf_p_model = train(G3~., data=trainingPca, method="rf", metric="RMSE", tuneGrid=tunegrid, trControl=control)

testingPca = data.frame(cbind((scale(testSet))%*%pcaThing$rotation[,1:19],G3 = testSet$G3))

rf_p_pred = predict(rf_p_model,testingPca)

varImp(rf_model)

plotty = data.frame(testing = testingPca$G3,prediction = rf_p_pred)
print(ggplot(plotty, aes(x=testing, y=prediction)) + xlab("testSet") + ylab("prediction") +
        geom_point(size=3, colour="red", alpha=0.9) + geom_point(size=1, colour="black", alpha=0.9) +
        theme(plot.title = element_text(hjust = 0.5)) + ggtitle("testSet & prediction"))


rmse_func(rf_p_model,testingPca,"G3")

#conclusion
rmse_func(rtree_model,testSet,"G3")
rmse_func(tbag_model,testSet,"G3")
rmse_func(rf_model,testSet,"G3")
rmse_func(rf_p_model,testingPca,"G3")

