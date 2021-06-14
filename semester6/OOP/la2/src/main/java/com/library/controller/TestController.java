package com.library.controller;

import javax.annotation.security.RolesAllowed;

import com.library.dto.UserDTO;
import com.library.service.UserService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
@CrossOrigin(origins = "http://localhost:3000")
public class TestController {

    private UserService userService;

    @Autowired
    public TestController(UserService userService) {
      this.userService = userService;
    }

    @RequestMapping(value = "/anonymous", method = RequestMethod.GET)
    public ResponseEntity<String> getAnonymous() {
        return ResponseEntity.ok("Hello Anonymous");
    }

    @RolesAllowed({"user", "admin"})
    @RequestMapping(value = "/user", method = RequestMethod.GET)
    public ResponseEntity<UserDTO> getUser(@RequestHeader String Authorization) {
        UserDTO userdto = userService.getUserDto(Authorization);
        System.out.println(userdto.getName());
        System.out.println(userdto.getSurname());
        System.out.println(userdto.getLogin());
        System.out.println(userdto.getRole());
        
        return ResponseEntity.ok(userdto);
    }

    @RolesAllowed("admin")
    @RequestMapping(value = "/admin", method = RequestMethod.GET)
    public ResponseEntity<String> getAdmin(@RequestHeader String Authorization) {
        return ResponseEntity.ok("Hello Admin");
    }

    @RolesAllowed({ "admin", "user" })
    @RequestMapping(value = "/all-user", method = RequestMethod.GET)
    public ResponseEntity<String> getAllUser(@RequestHeader String Authorization) {
        return ResponseEntity.ok("Hello All User");
    }


    @RolesAllowed({ "admin", "user" })
    @RequestMapping(value = "/user/list_books", method = RequestMethod.GET)
    public ResponseEntity<String> getAllBooks(@RequestHeader String Authorization) {
        return ResponseEntity.ok("Hello All User");
    }
}