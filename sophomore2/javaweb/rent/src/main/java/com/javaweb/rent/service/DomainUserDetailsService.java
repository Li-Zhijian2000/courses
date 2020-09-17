package com.javaweb.rent.service;

import com.javaweb.rent.domain.Staff;
import com.javaweb.rent.domain.Tenant;
import com.javaweb.rent.repository.StaffRepository;
import com.javaweb.rent.repository.TenantRepository;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class DomainUserDetailsService implements UserDetailsService {

    private final Logger log = LoggerFactory.getLogger(UserService.class);
    
    private final TenantRepository tenantRepository;
    private final StaffRepository staffRepository;

    @Autowired
    public DomainUserDetailsService(TenantRepository tenantRepository, StaffRepository staffRepository, PasswordEncoder passwordEncoder) {
        this.tenantRepository = tenantRepository;
        this.staffRepository = staffRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        Tenant tenant = tenantRepository.findOneByUsername(username).orElse(null);
        
        log.info("find tenant {}: {}", username, tenant);

        if (tenant != null)
            return tenant;
        
        Staff staff = staffRepository.findOneByUsername(username).orElse(null);

        log.info("find staff {}: {}", username, staff);

        if (staff != null)
            return staff;

        throw new UsernameNotFoundException(String.format("User %s not found", username));
    }
    
}
