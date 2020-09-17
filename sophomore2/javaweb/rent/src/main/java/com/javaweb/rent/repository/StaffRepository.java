package com.javaweb.rent.repository;

import java.util.Optional;

import com.javaweb.rent.domain.Staff;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface StaffRepository extends JpaRepository<Staff, Long> {
    
    Optional<Staff> findOneByUsername(String username);

}