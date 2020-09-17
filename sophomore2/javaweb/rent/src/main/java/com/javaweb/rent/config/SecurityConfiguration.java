package com.javaweb.rent.config;


import java.io.PrintWriter;
import java.io.Serializable;

import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.javaweb.rent.domain.Staff;
import com.javaweb.rent.domain.Tenant;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.http.HttpMethod;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;

import lombok.AllArgsConstructor;
import lombok.Data;

@EnableWebSecurity
@EnableGlobalMethodSecurity(prePostEnabled = true, securedEnabled = true)
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {

    @Autowired
    private UserDetailsService userDetailsService;

    @Bean
    public PasswordEncoder encoder() {
        return new BCryptPasswordEncoder();
    }
    
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth
            .userDetailsService(userDetailsService)
            .passwordEncoder(encoder());
    }

    @Override
    public void configure(WebSecurity web) {
        web.ignoring()
            .antMatchers(HttpMethod.OPTIONS, "/**")
            .antMatchers("/app/**/*.{js,html}")
            .antMatchers("/content/**")
            .antMatchers("/h2-console/**")
            .antMatchers("/swagger-ui/index.html")
            .antMatchers("/test/**");
    }

    @Override
    public void configure(HttpSecurity http) throws Exception {
        @Data
        @AllArgsConstructor
        final class loginReturnVM implements Serializable {
            private static final long serialVersionUID = 1L;
            String username;
            String role;
        }
        // @formatter:off
        http            
            .formLogin()
            .loginProcessingUrl("/account/login")
            .successHandler((req, resp, authentication) -> {
                
                resp.setStatus(HttpServletResponse.SC_OK);
                Object principal = authentication.getPrincipal();
                resp.setContentType("application/json;charset=utf-8");
                String json = null;
                if (principal instanceof Tenant) {
                    json = new ObjectMapper().writeValueAsString(new loginReturnVM(((Tenant) principal).getUsername(), Constants.TENANT));
                }
                if (principal instanceof Staff) {
                    json = new ObjectMapper().writeValueAsString(new loginReturnVM(((Staff) principal).getUsername(), Constants.STAFF));
                }
                PrintWriter out = resp.getWriter();
                out.write(json);
                out.flush();
                out.close();
            })
            .failureHandler((req, resp, exception) -> {
                resp.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                resp.setContentType("application/json;charset=utf-8");
                PrintWriter out = resp.getWriter();
                out.write(exception.getMessage());
                out.flush();
                out.close();
            })
            // .permitAll()
        .and()
            .logout()
            .logoutUrl("/account/logout")
            .logoutSuccessHandler((req, resp, authentication) -> {
                resp.setStatus(HttpServletResponse.SC_OK);
            })
            // .permitAll()
        // .and()
        //     .authorizeRequests()
        //     .antMatchers("/acount/register").permitAll()
        //     .antMatchers("/account/**").hasAnyAuthority(Constants.STAFF, Constants.TENANT)
        //     .antMatchers("/staff/**").hasAuthority(Constants.STAFF)
        //     .antMatchers("/tenant/**").hasAuthority(Constants.TENANT)
        .and()
            .csrf().disable();
    }
}
