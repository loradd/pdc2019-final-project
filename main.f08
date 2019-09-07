program bucket_test 
    use sort_mod 
    implicit none 

!      real(8), dimension(1:10) :: sort = (/1.d0,6.d0,8.d0,2.d0,11.d0,101.d0,56.d0,2.d0,4.d0,10.d0/) 
    real(8), dimension(1:100000000) :: sort 
    call random_number(sort) 



    call bucket(sort,4) 
    write(*,*) "Sorted array:" 
    write(*,'(10f8.4)') sort(1:1000)

end program bucket_test 
