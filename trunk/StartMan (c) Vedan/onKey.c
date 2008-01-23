else//Если юзеров больше, то 
   {
   if (UZERS==1)//Активен режим одного
   {
     if (strstr((char*)PASSWORD_SET1,nullpass)) 
     {
       RunElfs(); CloseCSM(MAINCSM_ID);
     }
     else
     {
       GetpassINFO();
     }
   }
   if (UZERS==2)//Активен режим двух
   { 
     if(y==59)
     { 
     if (strstr((char*)PASSWORD_SET1,nullpass))
     {
     RunElfs();  
     CloseCSM(MAINCSM_ID);
     }
     else {GetpassINFO();}
     }
     else
     {
      if(y==91)
      {
       if (strstr((char*)PASSWORD_SET2,nullpass))
       {
       RunElfs();  
       CloseCSM(MAINCSM_ID);
       }
       else {GetpassINFO();}
       }
     }
  }
  else
  if (UZERS==3)
  { 
  if(y==43)
 { 
     if (strstr((char*)PASSWORD_SET1,nullpass))
     {
     RunElfs();  
     CloseCSM(MAINCSM_ID);
     }
     else {GetpassINFO();}
     }
     else
     {
  if(y==75)
  {
       if (strstr((char*)PASSWORD_SET2,nullpass))
       {
       RunElfs();  
       CloseCSM(MAINCSM_ID);
       }
       else {GetpassINFO();}
       }
  if(y==107)
   {
       if (strstr((char*)PASSWORD_SET2,nullpass))
       {
       RunElfs();  
       CloseCSM(MAINCSM_ID);
       }
       else {GetpassINFO();}
       }
      }
      }
      else
        
//Для безпарольного входа///////////////////////////////////////////////////////
   if (ENA_PASS==0)
   {     
     if (UZERS==1)
     {
     RunElfs();CloseCSM(MAINCSM_ID);
     }
     if (UZERS==2)
     { 
        if(y==59)
        {
        RunElfs();CloseCSM(MAINCSM_ID);
        }
        if(y==91)
        {
        RunElfs();CloseCSM(MAINCSM_ID);
        }
     }
     if (UZERS==3)
     { 
        if(y==43)
        {   
        RunElfs();CloseCSM(MAINCSM_ID);
        }
        if(y==75)
        {
        RunElfs();  
        }
        if(y==107)
        {
        RunElfs();CloseCSM(MAINCSM_ID);
        }
     }
   }  
////////////////////////////////////////////////////////////////////////////////
 if (ENA_PASS==0)
    {     
     if (UZERS==1)RunElfs();CloseCSM(MAINCSM_ID);
     if (UZERS==2)
        { 
        if(y==59) void RUC(); else
        if(y==91) void RUC();
        }
     if (UZERS==3)
        { 
        if(y==43) void RUC(); else
        if(y==75) void RUC(); else
        if(y==107)void RUC();
        }
    }
     
     