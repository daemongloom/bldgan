//условие открытия//////////////////////////////////////////////////////////////
  if (UZERS==1)
  {
  strcpy(dname,DIR_RUN_DE1);
  }
  else
  {
   if (UZERS==2)
    { 
     if(y==59)
     {
     strcpy(dname,DIR_RUN_DE1);
     }
     else
     {
     if(y==91)
     {
     strcpy(dname,DIR_RUN_DE2);
     }
    }
   }
  }
  else
  {
   if (UZERS==3)
    { 
     if(y==43)
      {
      strcpy(dname,DIR_RUN_DE1);
      }
     else
    {
     if(y==75)
     {
     strcpy(dname,DIR_RUN_DE2);
     }
    }
    else
   {
   if(y==107)
   {
   strcpy(dname,DIR_RUN_DE3);
   }
  } 
 }
}

////////////////////////////////////////////////////////////////////////////////
  if (UZERS==1) strcpy(dname,DIR_RUN_DE1);
  if (UZERS==2)
     { 
     if(y==59) strcpy(dname,DIR_RUN_DE1);else
     if(y==91) strcpy(dname,DIR_RUN_DE2);
     }
  if (UZERS==3)
     { 
     if(y==43) strcpy(dname,DIR_RUN_DE1);else
     if(y==75) strcpy(dname,DIR_RUN_DE2);else
     if(y==107)strcpy(dname,DIR_RUN_DE3);
     }
////////////////////////////////////////////////////////////////////////////////
