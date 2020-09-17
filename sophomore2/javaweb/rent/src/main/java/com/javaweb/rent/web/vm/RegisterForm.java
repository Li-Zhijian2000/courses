package com.javaweb.rent.web.vm;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Pattern;
import javax.validation.constraints.Size;

import com.javaweb.rent.config.Constants;

import lombok.Data;

@Data
public class RegisterForm {
    
    @NotNull
    @Pattern(regexp = Constants.USERNAME_REGEX)
    @Size(min = 2, max = 10)
    private String username;

    @NotNull
    @Size(min = 6, max = 10)
    private String password;

    @NotNull
    @Pattern(regexp = Constants.AUTHORITY_REGEX)
    private String role;
    
}