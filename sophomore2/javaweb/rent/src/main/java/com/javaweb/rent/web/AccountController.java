package com.javaweb.rent.web;

import javax.validation.Valid;

import com.javaweb.rent.service.UserService;
import com.javaweb.rent.service.error.EmailAlreadyUsedException;
import com.javaweb.rent.web.vm.RegisterForm;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/account")
public class AccountController {

    private final UserService userService;

    @Autowired
    public AccountController(UserService userService) {
        this.userService = userService;
    }

    @PostMapping("/register")
    @ResponseStatus(HttpStatus.CREATED)
    public void registerAccount(@Valid @RequestBody RegisterForm form) {
        userService.register(form);
    }

    // @GetMapping("/activate")
    // @ResponseStatus(HttpStatus.OK)
    // public void activateAccount(@RequestParam(value = "key") String key) {
    // Optional<User> user = userService.activateRegistration(key);
    // user.orElseThrow(() -> new AccountResourceException("No user was found for
    // this activation key"));
    // }

    // @PostMapping("/staff/register")
    // @ResponseStatus(HttpStatus.CREATED)
    // public void registerStaff(@Valid @RequestBody RegisterStaffForm form) {
    // userService.registerStaff(form);
    // }
}