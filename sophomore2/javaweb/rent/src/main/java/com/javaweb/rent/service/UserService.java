package com.javaweb.rent.service;

import com.javaweb.rent.config.Constants;
import com.javaweb.rent.domain.Staff;
import com.javaweb.rent.domain.Tenant;
import com.javaweb.rent.repository.StaffRepository;
import com.javaweb.rent.repository.TenantRepository;
import com.javaweb.rent.service.error.UsernameAlreadyUsedException;
import com.javaweb.rent.web.vm.RegisterForm;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    
    private final Logger log = LoggerFactory.getLogger(UserService.class);
    
    private final TenantRepository tenantRepository;
    private final StaffRepository staffRepository;
    private final PasswordEncoder passwordEncoder;

    @Autowired
    public UserService(TenantRepository tenantRepository, StaffRepository staffRepository, PasswordEncoder passwordEncoder) {
        this.tenantRepository = tenantRepository;
        this.staffRepository = staffRepository;
        this.passwordEncoder = passwordEncoder;
    }

    public UserDetails register(RegisterForm form) {
        tenantRepository.findOneByUsername(form.getUsername()).ifPresent(existingUser -> {
            log.info("Username {} already used", existingUser.getUsername());
            throw new UsernameAlreadyUsedException();
        });
        
        staffRepository.findOneByUsername(form.getUsername()).ifPresent(existingUser -> {
            log.info("Username {} already used", existingUser.getUsername());
            throw new UsernameAlreadyUsedException();
        });

        // tenantRepository.findOneByEmailIgnoreCase(form.getEmail()).ifPresent(existingTenant -> {
        //     log.info("Email {} already used", existingTenant.getEmail());
        //     throw new EmailAlreadyUsedException();
        // });

        String encryptedPassword = passwordEncoder.encode(form.getPassword());
        if (form.getRole().equals(Constants.TENANT)) {
            Tenant newTenant = Tenant.builder()
                .username(form.getUsername())
                .password(encryptedPassword)
                .build();
            
            tenantRepository.save(newTenant);
            log.info("Created Information for Tenant: {}", newTenant);
            return newTenant;
        }
        
        if (form.getRole().equals(Constants.STAFF)) {
            Staff newStaff = Staff.builder()
                .username(form.getUsername())
                .password(encryptedPassword)
                .build();
            
            staffRepository.save(newStaff);
            log.info("Created Information for Staff: {}", newStaff);
            return newStaff;
        }

        throw new RuntimeException("no such role");
    }

    // public Optional<Tenant> activateRegistration(String key) {
    //     log.info("Activating tenant for activation key {}", key);
    //     return tenantRepository.findOneByActivationKey(key)
    //         .map(tenant -> {
    //             tenant.setActivated(true);
    //             tenant.setActivationKey(null);
    //             tenantRepository.save(tenant);
    //             log.info("Activated tenant: {}", tenant);
    //             return tenant;
    //         });
    // }

}