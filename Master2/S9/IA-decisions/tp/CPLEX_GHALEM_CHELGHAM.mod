/*********************************************
 * OPL 22.1.1.0 Model
 * Author: Agee
 * Creation Date: 2 nov. 2024 at 20:02:09
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

//{int} PossibleStartDates = { DD[ima, ins] | ima in Images, ins in Instruments };

// selection[i] = 1 <=> 
//    image i is selected and realized
dvar int selection[Images] in bool;

// assignedTo[ima, ins] = 1 <=> 
//     image ima  has been selected and assigned to  instrument ins
dvar int assignedTo[Images, Instruments] in bool;


 
 

// propability that image ima will be correctly aquired by the instrument that has been assigne to it
// dvar float probaInstrumentOK[Images] in  0..1;
 
 //dexpr float probaInstrumentOK[ima in Images] = 
 //   sum(ins in Instruments) (assignedTo[ima][ins] * (1 - Failure[ins]));
 

// Maximize the sum of the payoffs.
//maximize sum(ima in Images) (PA[ima] * selection[ima]) ;


//Maximiser le gain ... ici on n'a pas encore pris en compte les incertitudes'
maximize (sum(ima in Images : TY[ima] == 1)
    (PA[ima] * (1 - ProbaSup[ima]) * selection[ima] *
    (1 - (sum(ins in Instruments ) assignedTo[ima,ins] * Failure[ins] ))))
                 
    	 +
          
         (sum(ima in Images : TY[ima] == 2)
     (PA[ima] * (1 - ProbaSup[ima]) * selection[ima] *
     (1 - (Failure[1] + Failure[3] - Failure[1] * Failure[3] ))));      
                 
                 
// Ou ça
//maximize sum(ima in Images)
	//(PA[ima]*selection[ima]*(1-(ProbaSup[ima]))*
	//(1-((assignedTo[ima,1]*Failure[1]+
			//assignedTo[ima,2]*Failure[2]+
			//assignedTo[ima,3]*Failure[3])*
			//(1/TY[ima]))));

constraints {

   // consider one instrument
   // if, on this instrument the time of transition between the end of an image and the
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
     
   sum(im in Images) selection[im] * PM[im] <= PMmax;
   
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
 