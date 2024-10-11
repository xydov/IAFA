/*********************************************
 * OPL 12.7.1.0 Model
 * Author: fargier
 * Creation Date: 3 nov 2023 at 13:50:16
 *********************************************/

 
//using CP;  // decomment for CP solver instead of LP solver

 
int NbImages = ... ;

range Images = 1 .. NbImages ;

// type of the images, 1 for mono, 2 for stereo
int TY[Images] = ... ;
 

// Memory required for each image
int PM[Images] = ... ;

// payoff of each image
int PA[Images] = ... ;


// Probability of Cloudy Weather
float ProbaInf[Images] = ... ;
float ProbaSup[Images] = ... ;



int NbInstruments = ... ;
range Instruments = 1 .. NbInstruments ;

// probability of failure of each instrument
float Failure[Instruments] = ...;

// starting time of each image, depending on the instrument
int DD[Images, Instruments] = ... ;

// depointing angle of each image, depeding on the instrument
int AN[Images, Instruments] = ... ;

// duration of acquisition, common to all the image
int DU = ... ;

// rotation speed of the instruments
int VI = ... ;

 

// Capacity of the memory
int PMmax = ... ;

range bool = 0 .. 1 ;

{int} PossibleStartDates = { DD[ima, ins] | ima in Images, ins in Instruments };

// selection[i] = 1 <=> 
//    image i is selected and realized
dvar int selection[Images] in bool;

// assignedTo[ima, ins] = 1 <=> 
//     image ima  has been selected and assigned to  instrument ins
dvar int assignedTo[Images, Instruments] in bool;


 
 

// propability that image ima will be correctly aquired by the instrument that has been assigne to it
 dvar float probaInstrumentOK[Images] in  0..1;
 

// Maximize the sum of the payoffs.
//maximize sum(ima in Images) (PA[ima] * selection[ima]) ;


//Maximiser le gain ... ici on n'a pas encore pris en compte les incertitudes'
maximize sum(ima in Images) 
	(PA[ima]*selection[ima]);

constraints {

   // consider one instrument
   // if, on this instrument the time of transition betwwen the end of the an image and the
   // beginning of another one is not sufficient ,
   // it is not possible to realized both on that instrument.
   forall(ordered ima1, ima2 in Images, ins in Instruments : 
             abs(DD[ima1,ins] - DD[ima2,ins]) * VI 
             <  DU  * VI + abs(AN[ima1,ins] - AN[ima2,ins]) 
         ) {
      assignedTo[ima1,ins] + assignedTo[ima2,ins] <= 1 ;
   };
   
   forall(im in Images:TY[im]==1) //image mono assignee
     {
       sum(ins in Instruments)assignedTo[im,ins]==selection[im];
     };
   
   forall(im in Images:TY[im]==2) //image stereo assignee
     {
       assignedTo[im,1]==selection[im];
       assignedTo[im,3]==selection[im];
       assignedTo[im,2]==0;
     };
     
   // il ne vous reste que la contrainte de memoire à implementer
   
}
 
 /****************************/
/* Output   */
/****************************/

execute{

 for(var ima in Images)
    for (var ins in Instruments)
    { 
    if (assignedTo[ima][ins] > 0)  {
          
      writeln("Image" +  ima + "  on  " + ins + " at date " + DD[ima][ins]); 
}}}  
 