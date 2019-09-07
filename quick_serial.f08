recursive subroutine quicksort(low,high,tbsort) 
    use omp_lib 
    implicit none 

    integer, intent(in)                  :: low     ! lower index
    integer, intent(in)                  :: high    ! higher index  
    real(8), dimension(:), intent(inout) :: tbsort  ! Array to be sorted 

!Local variable 
    real(8) :: pivot  ! self explaining 
    integer :: i,j    ! Used as new low, high for recursive call  
    real(8) :: t      ! Temp to save right most 

! Choose mid value as pivot 

    pivot = tbsort(int((low+high)/2)) 

    i     = low 
    j     = high 


!Infinite loop     
    do  
        do while(tbsort(i).lt.pivot) 
            i = i+1 
        end do 
        do while(pivot.lt.tbsort(j)) 
            j = j-1 
        end do 
!Swap things 
        if ( i.le.j ) then 
            t = tbsort(i)          ! Right most value in partition i 
            tbsort(i) = tbsort(j)  ! Swap with left most value in partition j 
            tbsort(j) = t          ! Swap with righ most value in partition i 
            i = i+1 
            j = j-1 
        end if 

        if (i.gt.j) exit           ! Partitions should be sorted now 

     end do 
     
! Recursion  use j as new high 
    if ( low.lt.j ) then 
!$OMP TASK shared(tbsort) 
        call quicksort(low, j  ,tbsort)   
!$OMP END TASK 
    end if 
    
    if ( i.lt.high )then 
!$OMP TASK shared(tbsort) 
        call quicksort(i  ,high,tbsort)  
!$OMP END TASK 
    end if 

end subroutine quicksort

