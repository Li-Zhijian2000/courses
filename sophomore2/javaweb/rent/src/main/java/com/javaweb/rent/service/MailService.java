// package com.javaweb.rent.service;

// import java.net.InetAddress;
// import java.net.UnknownHostException;
// import java.nio.charset.StandardCharsets;

// import javax.mail.MessagingException;
// import javax.mail.internet.MimeMessage;

// import com.javaweb.rent.domain.User;

// import org.slf4j.Logger;
// import org.slf4j.LoggerFactory;
// import org.springframework.beans.factory.annotation.Autowired;
// import org.springframework.core.env.Environment;
// import org.springframework.mail.MailException;
// import org.springframework.mail.javamail.JavaMailSender;
// import org.springframework.mail.javamail.MimeMessageHelper;
// import org.springframework.scheduling.annotation.Async;
// import org.springframework.stereotype.Service;

// @Service
// public class MailService {
    
//     private final Logger log = LoggerFactory.getLogger(MailService.class);

//     private final JavaMailSender javaMailSender;

//     private final Environment env;

//     @Autowired
//     public MailService(Environment env, JavaMailSender javaMailSender) {
//         this.env = env;
//         this.javaMailSender = javaMailSender;
//     }

//     @Async
//     public void sendEmail(String to, String subject, String content, boolean isMultipart, boolean isHtml) {
//         log.info("Send email[multipart '{}' and html '{}'] to '{}' with subject '{}' and content={}",
//             isMultipart, isHtml, to, subject, content);

//         // Prepare message using a Spring helper
//         MimeMessage mimeMessage = javaMailSender.createMimeMessage();
//         try {
//             MimeMessageHelper message = new MimeMessageHelper(mimeMessage, isMultipart, StandardCharsets.UTF_8.name());
//             message.setFrom("13261806700@163.com");
//             message.setTo(to);
//             message.setSubject(subject);
//             message.setText(content, isHtml);
//             javaMailSender.send(mimeMessage);
//             log.info("Sent email to User '{}'", to);
//         }  catch (MailException | MessagingException e) {
//             log.warn("Email could not be sent to user '{}'", to, e);
//         }
//     }

//     @Async
//     public void sendActivationEmail(User user) {
//         log.info("Sending activation email to '{}'", user.getEmail());
        
//         String protocol = "http";
//         if (env.getProperty("server.ssl.key-store") != null) {
//             protocol = "https";
//         }
//         String serverPort = env.getProperty("server.port");
//         serverPort = "8080";
//         String hostAddress = "localhost";
//         try {
//             hostAddress = InetAddress.getLocalHost().getHostAddress();
//         } catch (UnknownHostException e) {
//             log.warn("The host name could not be determined, using `localhost` as fallback");
//         }
//         String subject = "rent account activation is required";

//         String activateUrl = String.format("%s://%s:%s/#/account/activate?key=%s", protocol, hostAddress, serverPort, user.getActivationKey());

//         String text = String.format(
//             "Your myapp account has been created, please click on the URL below to activate it:" + 
//             "<a href=\"%s\">%s</a>", activateUrl, activateUrl);
            
//         sendEmail(user.getEmail(), subject, text, false, true);
//     }
// }