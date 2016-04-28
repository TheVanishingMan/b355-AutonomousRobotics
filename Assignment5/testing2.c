float forwardKinY(float theta1, float theta2, float l1, float l2){
	float alpha = PI - theta1 - theta2;
	return (l1*sin(theta1)) + (l2 * sin(alpha));
}

float forwardKinX(float theta1, float theta2, float l1, float l2){
	float alpha = PI - theta1 - theta2;
	return (l1*cos(theta1)) - (l2 * cos(alpha));
}

float thetaTwo(float x, float y, float l1, float l2) {
	float answer1 = (x*x)+(y*y)-(l1*l1)-(l2*l2);
	float answer2 = answer1/(2*l1*l2);
	float answer3 = acos(answer2);
	return answer3;
}


float thetaOne(float x, float y, float theta2, float l2) {
	float answer1 = l2*sin(theta2);
	float answer2 = (x*x)+(y*y);
	float answer3 = sqrt(answer2);
	float answer4 = answer1/answer3;
	float answer5= asin(answer4);
	float answer6 = answer5;
	float answer7 = y/x;
	float answer8 = atan(answer7);
	float answer9 = answer8;
	float answer10 = answer9-answer6;
	return answer10;
}

task main()
{

float t2 = thetaTwo(35,10,37,20);
writeDebugStreamLine("theta2 is %f",t2);
float t1 = thetaOne(35,10,t2,20);
writeDebugStreamLine("theta1 is %f",t1);
float newX = forwardKinX(t1, t2, 37, 20);
float newY = forwardKinY(t1, t2, 37, 20);
writeDebugStreamLine("newX is %f",newX);
writeDebugStreamLine("newY is %f",newY );

}
