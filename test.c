#ifdef documentation
=========================================================================

     program: readEDF.c
          by: Shlomit Yuval-Greenberg (based on justin gardner code)
        date: 04/04/10

=========================================================================
#endif

/////////////////////////
//   include section   //
/////////////////////////
//#include "mgl.h"
#include "mex.h"
#include "edf.h"

// ///////////////////////////////
// //   function declarations   //
// ///////////////////////////////
// void dispEventType(int eventType);
// void dispEvent(int eventType, ALLF_DATA *event,int verbose);
// int isEyeUsedMessage(int eventType, ALLF_DATA *event);
// 
// 
// 
// ////////////////////////
// //   define section   //
// ////////////////////////
// #define STRLEN 2048
// /* this is a hack, taken from opt.h in the EDF example code */
// /* it is undocumented in the EyeLink code */
// #define NaN 1e8  /* missing floating-point values*/
// 
// //////////////
// //   main   //
// //////////////
// void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
// {
//   int err;
// 
//   // parse input arguments
//   if (nrhs<1) {
//     usageError("readEDF");
//     return;
//   }
//  
//   // get filename
//   char filename[STRLEN];
//   mxGetString(prhs[0], filename, STRLEN);
// 
//   // get verbose
//   int verbose = 1;
//   if (nrhs >= 2)
//     verbose = (int) *mxGetPr(prhs[1]); 
// 
//   // open file
//   if (verbose) mexPrintf("(readEDF) Opening EDF file %s\n",filename);
// 
//   int errval;
//   EDFFILE *edf = edf_open_file(filename,verbose,1,1,&errval);
//   // and check that we opened correctly
//   if (edf == NULL) {
//     mexPrintf("(readEDF) Could not open file %s (error %i)\n",filename,errval);
//     plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
//     return;
//   }
// 
//   // initialize some variables
//   int i,eventType,numSamples=0,numFix=0,numSac=0,numBlink=0;
//   int numMessages = 0;
//   int numElements = edf_get_element_count(edf);
//   int numTrials = edf_get_trial_count(edf);
//   int setGazeCoords = 0;
//   ALLF_DATA *data;
// 
// 
//   
//   // initialize the output structure
//   const char *fieldNames[] =  {"filename","numElements","numTrials",
// 			       "EDFAPI","preamble","gazeLeft","gazeRight",
// 			       "fixations","saccades","blinks","messages",
// 			       "gazeCoords","frameRate"};
//   int outDims[2] = {1,1};
//   plhs[0] = mxCreateStructArray(1,outDims,14,fieldNames);
//   
//   // save some info about the EDF file in the output
//   mxSetField(plhs[0],0,"filename",mxCreateString(filename));
//   mxSetField(plhs[0],0,"numElements",mxCreateDoubleScalar(numElements));
//   mxSetField(plhs[0],0,"numTrials",mxCreateDoubleScalar(numTrials));
//   mxSetField(plhs[0],0,"EDFAPI",mxCreateString(edf_get_version()));
// 
// 
// // save the preamble
//   int preambleLength = edf_get_preamble_text_length(edf);
//   char *cbuf = (char *)malloc(preambleLength*sizeof(char));
//   edf_get_preamble_text(edf,cbuf,preambleLength);
//   mxSetField(plhs[0],0,"preamble",mxCreateString(cbuf));
// 
//   // mark beginning of file
//   BOOKMARK startOfFile;
//   edf_set_bookmark(edf,&startOfFile);
// 
// 
//   // count number of samples and events in file
//   for (i=0;i<numElements;i++) {
//     // get the event type and event pointer
//     eventType = edf_get_next_data(edf);
//     data = edf_get_float_data(edf);
//     if (eventType == SAMPLE_TYPE) numSamples++;
//     if (eventType == ENDSACC) numSac++;
//     if (eventType == ENDFIX) numFix++;
//     if (eventType == ENDBLINK) numBlink++;
//     
//     if (eventType == MESSAGEEVENT){
//       // We'll keep track of all messages 
//       numMessages++;
// 
//       
//     }
//   }
// 
// 
//   // set an output fields for the gaze data
//   const char *fieldNamesGaze[] =  {"time","x","y","pupil","pix2degX","pix2degY","velocityX","velocityY","whichEye"};
//   int outDims2[2] = {1,1};
// 
//   // set gaze left fields
//   mxSetField(plhs[0],0,"gazeLeft",mxCreateStructArray(1,outDims2,9,fieldNamesGaze));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"time",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrTimeLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"time"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"x",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrXLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"x"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"y",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrYLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"y"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pupil",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPupilLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pupil"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pix2degX",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPix2DegXLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pix2degX"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pix2degY",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPix2DegYLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"pix2degY"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"velocityX",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrVelXLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"velocityX"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"velocityY",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrVelYLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"velocityY"));
//   mxSetField(mxGetField(plhs[0],0,"gazeLeft"),0,"whichEye",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrWhichEyeLeft = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeLeft"),0,"whichEye"));
// 
//   // set gaze right fields
//   mxSetField(plhs[0],0,"gazeRight",mxCreateStructArray(1,outDims2,9,fieldNamesGaze));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"time",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrTimeRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"time"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"x",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrXRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"x"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"y",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrYRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"y"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"pupil",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPupilRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"pupil"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"pix2degX",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPix2DegXRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"pix2degX"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"pix2degY",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrPix2DegYRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"pix2degY"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"velocityX",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrVelXRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"velocityX"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"velocityY",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrVelYRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"velocityY"));
//   mxSetField(mxGetField(plhs[0],0,"gazeRight"),0,"whichEye",mxCreateDoubleMatrix(1,numSamples,mxREAL));
//   double *outptrWhichEyeRight = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"gazeRight"),0,"whichEye"));
// 
//   // set output fields for fixations
//   const char *fieldNamesFix[] =  {"startTime","endTime","aveH","aveV"};
//   int outDimsFix[2] = {1,1};
//   mxSetField(plhs[0],0,"fixations",mxCreateStructArray(1,outDimsFix,4,fieldNamesFix));
//   mxSetField(mxGetField(plhs[0],0,"fixations"),0,"startTime",mxCreateDoubleMatrix(1,numFix,mxREAL));
//   double *outptrFixStartTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"fixations"),0,"startTime"));
//   mxSetField(mxGetField(plhs[0],0,"fixations"),0,"endTime",mxCreateDoubleMatrix(1,numFix,mxREAL));
//   double *outptrFixEndTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"fixations"),0,"endTime"));
//   mxSetField(mxGetField(plhs[0],0,"fixations"),0,"aveH",mxCreateDoubleMatrix(1,numFix,mxREAL));
//   double *outptrFixAvgH = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"fixations"),0,"aveH"));
//   mxSetField(mxGetField(plhs[0],0,"fixations"),0,"aveV",mxCreateDoubleMatrix(1,numFix,mxREAL));
//   double *outptrFixAvgV = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"fixations"),0,"aveV"));
// 
//   // set output fields for saccades
//   const char *fieldNamesSac[] =  {"startTime","endTime","startH","startV","endH","endV","peakVel"};
//   int outDimsSac[2] = {1,1};
//   mxSetField(plhs[0],0,"saccades",mxCreateStructArray(1,outDimsFix,7,fieldNamesSac));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"startTime",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacStartTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"startTime"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"endTime",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacEndTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"endTime"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"startH",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacStartH = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"startH"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"startV",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacStartV = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"startV"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"endH",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacEndH = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"endH"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"endV",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacEndV = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"endV"));
//   mxSetField(mxGetField(plhs[0],0,"saccades"),0,"peakVel",mxCreateDoubleMatrix(1,numSac,mxREAL));
//   double *outptrSacPeakVel = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"saccades"),0,"peakVel"));
// 
//   // set output fields for blinks
//   const char *fieldNamesBlinks[] =  {"startTime","endTime"};
//   int outDimsBlinks[2] = {1,1};
//   mxSetField(plhs[0],0,"blinks",mxCreateStructArray(1,outDimsBlinks,2,fieldNamesBlinks));
//   mxSetField(mxGetField(plhs[0],0,"blinks"),0,"startTime",mxCreateDoubleMatrix(1,numBlink,mxREAL));
//   double *outptrBlinkStartTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"blinks"),0,"startTime"));
//   mxSetField(mxGetField(plhs[0],0,"blinks"),0,"endTime",mxCreateDoubleMatrix(1,numBlink,mxREAL));
//   double *outptrBlinkEndTime = (double *)mxGetPr(mxGetField(mxGetField(plhs[0],0,"blinks"),0,"endTime"));
// 
//   
//   // Messages
//   const char *fieldNamesMessages[] = {"message", "time"};
//   int outDimsMessages[2] = {1, numMessages};
//   size_t messagesCounter = 0;
//   mxArray *messagesStruct = mxCreateStructArray(2, outDimsMessages, 2, fieldNamesMessages);
//   mxSetField(plhs[0], 0, "messages", messagesStruct); 
// 
//   // gaze coordinates
//   mxSetField(plhs[0],0,"gazeCoords",mxCreateDoubleMatrix(1,4,mxREAL));
//   double *outptrCoords = (double *)mxGetPr(mxGetField(plhs[0],0,"gazeCoords"));
// 
//   // gaze coordinates
//   mxSetField(plhs[0],0,"frameRate",mxCreateDoubleMatrix(1,1,mxREAL));
//   double *outptrFrameRate = (double *)mxGetPr(mxGetField(plhs[0],0,"frameRate"));
// 
//   // go back go beginning of file
//   edf_goto_bookmark(edf,&startOfFile);
//   
//   int currentEye = -1;
//   // go through all data in file
//   if (verbose) mexPrintf("(readEDF) Looping over samples and events \n");
// 
//   for (i=0;i<numElements;i++) {
//     // get the event type and event pointer
//     eventType = edf_get_next_data(edf);
//     data = edf_get_float_data(edf);
// 
//     // display event type and info
//     if (verbose>3) dispEvent(eventType,data,1); 
//     if (verbose>2) dispEventType(eventType);
//     if (verbose>1) dispEvent(eventType,data,0); 
//    
//     // get samples
//     switch(eventType) {
//     case SAMPLE_TYPE:
// 
//       // copy out left eye
//       currentEye = 0;
//       *outptrTimeLeft++ = (double)data->fs.time;
//       *outptrWhichEyeLeft++ = currentEye;
//       if ((int)data->fs.gx[currentEye]==NaN) {
//           *outptrXLeft++ = mxGetNaN();
//           *outptrYLeft++ = mxGetNaN();
//           *outptrPupilLeft++ = mxGetNaN();
//           *outptrPix2DegXLeft++ = mxGetNaN();
//           *outptrPix2DegYLeft++ = mxGetNaN();
//           *outptrVelXLeft++ = mxGetNaN();
//           *outptrVelYLeft++ = mxGetNaN();
//         }
//       else{
//         *outptrXLeft++ = (double)data->fs.gx[currentEye];
//         *outptrYLeft++ = (double)data->fs.gy[currentEye];
//         *outptrPupilLeft++ = (double)data->fs.pa[currentEye];
//         *outptrPix2DegXLeft++ = (double)data->fs.rx;
//         *outptrPix2DegYLeft++ = (double)data->fs.ry;
//         *outptrVelXLeft++ = (double)data->fs.gxvel[currentEye];
//         *outptrVelYLeft++ = (double)data->fs.gyvel[currentEye];
// 
//       }
//       // copy out right eye
//       currentEye = 1;
//       *outptrTimeRight++ = (double)data->fs.time;
//       *outptrWhichEyeRight++ = currentEye;
//       if ((int)data->fs.gx[currentEye]==NaN) {
//           *outptrXRight++ = mxGetNaN();
//           *outptrYRight++ = mxGetNaN();
//           *outptrPupilRight++ = mxGetNaN();
//           *outptrPix2DegXRight++ = mxGetNaN();
//           *outptrPix2DegYRight++ = mxGetNaN();
//           *outptrVelXRight++ = mxGetNaN();
//           *outptrVelYRight++ = mxGetNaN();
//         }
//       else{
//         *outptrXRight++ = (double)data->fs.gx[currentEye];
//         *outptrYRight++ = (double)data->fs.gy[currentEye];
//         *outptrPupilRight++ = (double)data->fs.pa[currentEye];
//         *outptrPix2DegXRight++ = (double)data->fs.rx;
//         *outptrPix2DegYRight++ = (double)data->fs.ry;
//         *outptrVelXRight++ = (double)data->fs.gxvel[currentEye];
//         *outptrVelYRight++ = (double)data->fs.gyvel[currentEye];
//       }
//       break;
//     case ENDFIX:
//       *outptrFixStartTime++ = (double)data->fe.sttime;
//       *outptrFixEndTime++ = (double)data->fe.entime;
//       *outptrFixAvgH++ = (double)data->fe.gavx;
//       *outptrFixAvgV++ = (double)data->fe.gavy;
//       break;
//     case ENDSACC:
//       *outptrSacStartTime++ = (double)data->fe.sttime;
//       *outptrSacEndTime++ = (double)data->fe.entime;
//       *outptrSacStartH++ = (double)data->fe.gstx;
//       *outptrSacStartV++ = (double)data->fe.gsty;
//       *outptrSacEndH++ = (double)data->fe.genx;
//       *outptrSacEndV++ = (double)data->fe.geny;
//       *outptrSacPeakVel++ = (double)data->fe.pvel;
//       break;
//     case ENDBLINK:
//       *outptrBlinkStartTime++ = (double)data->fe.sttime;
//       *outptrBlinkEndTime++ = (double)data->fe.entime;
//       break;
//     case MESSAGEEVENT:
//         // Store all messages 
//         mxSetField(messagesStruct, messagesCounter, "message", mxCreateString(&(data->fe.message->c)));
//         mxSetField(messagesStruct, messagesCounter, "time", mxCreateDoubleScalar((double)data->fe.sttime));
//         messagesCounter++;
//         
//      
//       if ((strncmp(&(data->fe.message->c),"GAZE_COORDS",11) == 0) && (setGazeCoords == 0)) {
//         char *gazeCoords = &(data->fe.message->c);
//         char *tok;
//         tok = strtok(gazeCoords," ");
//         tok = strtok(NULL," ");
//         *outptrCoords++ = (double)atoi(tok);
//         tok = strtok(NULL," ");
//         *outptrCoords++ = (double)atoi(tok);
//         tok = strtok(NULL," ");
//         *outptrCoords++ = (double)atoi(tok);
//         tok = strtok(NULL," ");
//         *outptrCoords++ = (double)atoi(tok);
//         setGazeCoords = 1;
//       }
//       if (strncmp(&(data->fe.message->c),"FRAMERATE",9) == 0){
//         char *msg = &(data->fe.message->c);
//         char *tok;
//         tok = strtok(msg, " ");
//         tok = strtok(NULL," ");
//         *outptrFrameRate++ = (double)atof(tok);
//       }
//       /* if (strncmp(&(data->fe.message->c),"!CAL",4) == 0){ */
//       /*   char *calMessage = &(data->fe.message->c); */
//       /*   char *tok; */
//       /*   tok = strtok(calMessage, " "); */
//       /*   tok = strtok(NULL," "); */
//       /*   mexPrintf("%s\n", tok); */
//       /* } */
//       break;
//     }
//   }
// 
//   
//   
//   // free the bookmark
//   edf_free_bookmark(edf,&startOfFile);
// 
//   // close file
//   err = edf_close_file(edf);
//   if (err) {
//     mexPrintf("(readEDF) Error %i closing file %s\n",err,filename);
//   }
// }
// 
//    
// ///////////////////////
// //   dispEventType   //
// ///////////////////////
// void dispEventType(int dataType)
// {
//   mexPrintf("(readEDF) DataType is %i: ",dataType); 
//   switch(dataType)  {
//     case STARTBLINK:
//       mexPrintf("start blink");break;
//     case STARTSACC:
//       mexPrintf("start sacc");break;
//     case STARTFIX:
//       mexPrintf("start fix");break;
//     case STARTSAMPLES:
//       mexPrintf("start samples");break;
//     case STARTEVENTS:
//       mexPrintf("start events");break;
//     case STARTPARSE:
//       mexPrintf("start parse");break;
//     case ENDBLINK:
//       mexPrintf("end blink");break;
//     case ENDSACC:
//       mexPrintf("end sacc");break;
//     case ENDFIX:
//       mexPrintf("end fix");break;
//     case ENDSAMPLES:
//       mexPrintf("end samples");break;
//     case ENDEVENTS:
//       mexPrintf("end events");break;
//     case ENDPARSE:
//       mexPrintf("end parse");break;
//     case FIXUPDATE:
//       mexPrintf("fix update");break;
//     case BREAKPARSE:
//       mexPrintf("break parse");break;
//     case BUTTONEVENT:
//       mexPrintf("button event");break;
//     case INPUTEVENT:
//       mexPrintf("input event");break;
//     case MESSAGEEVENT:
//       mexPrintf("message event");break;
//     case SAMPLE_TYPE:
//       mexPrintf("sample type");break;
//     case RECORDING_INFO:
//       mexPrintf("recording info");break;
//     case NO_PENDING_ITEMS:
//       mexPrintf("no pending items");break;
//       break;
//   }
//   mexPrintf("\n");
// }
// 
// //////////////////////////
// //   isEyeUsedMessage   //
// //////////////////////////
// int isEyeUsedMessage(int eventType,ALLF_DATA *event)
// {
//   if (eventType == MESSAGEEVENT) {
//     if (strlen(&(event->fe.message->c)) > 8) {
//       if (strncmp(&(event->fe.message->c),"EYE_USED",8) == 0) {
// 	return 1;
//       }
//     }
//   }
//   return 0;
// }
// 
// 
// 
// ///////////////////
// //   dispEvent   //
// ///////////////////
// void dispEvent(int eventType,ALLF_DATA *event,int verbose)
// {
//   if (eventType == SAMPLE_TYPE) {
//     if (verbose) {
// 	mexPrintf("(readEDF) Sample eye 0 is %i: pupil [%f %f] head [%f %f] screen [%f %f] pupil size [%f]\n",event->fs.time,event->fs.px[0],event->fs.py[0],event->fs.hx[0],event->fs.hy[0],event->fs.gx[0],event->fs.gy[0],event->fs.pa[0]);
// 	mexPrintf("(readEDF) Sample eye 1 is %i: pupil [%f %f] head [%f %f] screen [%f %f] pupil size [%f]\n",event->fs.time,event->fs.px[1],event->fs.py[1],event->fs.hx[1],event->fs.hy[1],event->fs.gx[1],event->fs.gy[1],event->fs.pa[1]);
//       }
//   }
// }
// 
// 
