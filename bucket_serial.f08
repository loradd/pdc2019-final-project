subroutine bucket(inparr, numbuc )
    implicit none 
    real(8), dimension(:), intent(inout) :: inparr  ! Array to be sorted
    integer, intent(in) :: numbuc                   ! Number of buckets to be used

    real(8) :: maxarr, recima                       ! maximal value in input_array  and its reciprocal
    integer :: buckin                               ! Bucketindex computed as floor(numbuck*array(i)/maxval)
    integer :: ininde                               ! extent of input array 
    real(8), dimension(:,:), allocatable :: buckets ! The actual buckets. col=# elements in input, row=# of buckets
    real(8), dimension(:), allocatable :: auxbuc    ! auxilliary bucket to get rid of the zeros 

    real(8) :: t1,t2                                ! For timing 
    integer :: i,j 

    

    ininde = ubound(inparr,1)  
    maxarr = maxval(inparr)
    recima = (1/maxarr)*numbuc 

    allocate(buckets(1:ininde,1:numbuc)) 
    do i = 1, ininde 
        buckin = ceiling(inparr(i)*recima)     ! Ceiling returns integer, not like stupid C.
        buckets(i,buckin) = inparr(i)                 ! Put it into the bucket
    end do 


    allocate(auxbuc(1:ininde)) 
    ininde = 0 
    do i = 1, numbuc 
        auxbuc = pack(buckets(:,i),buckets(:,i).ne.0)
        call quicksort(1,ubound(auxbuc,1),auxbuc)
!Copy back to inparr 
        do j = 1, ubound(auxbuc,1) 
            ininde = ininde + 1 
            inparr(ininde) = auxbuc(j) 
        end do 
    end do 
    
end subroutine bucket 
