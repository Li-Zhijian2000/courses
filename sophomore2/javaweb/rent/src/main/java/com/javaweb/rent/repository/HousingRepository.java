package com.javaweb.rent.repository;

import java.util.List;

import com.javaweb.rent.domain.Housing;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface HousingRepository extends JpaRepository<Housing, Long> {
    
    List<Housing> findByRegionContaining(String key);

    List<Housing> findByCommunityContaining(String key);
    
}
